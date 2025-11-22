import os
import struct
from cffi import FFI
import random
import time
import array

ffi = FFI()
ffi.cdef("""
    void quick(int* start, int* end);
""")
qsort = ffi.dlopen("./libqsort.so")


def qsort_cffi(py_list: list) -> None:
    array_len = len(py_list)    
    c_arr = ffi.new("int[]", py_list)           # c_arr = int[]자료형에 py_list를 담음
    start_ptr = c_arr                           # start_ptr, end_ptr 선언은 쉬운편
    end_ptr = c_arr + array_len 
    qsort.quick(start_ptr, end_ptr)             # type: ignore
    res:list = ffi.unpack(c_arr, array_len)     # type: ignore

    # 매개변수를 직접 수정할 수 없어 진행함. (메모리 오버헤드 증가. 함수 실행시간 상승)
    for i in range(array_len):
        py_list[i] = res[i]


# array.array 를 사용하면 list 처럼 내부에 복사할 필요 없이 원본을 수정할 수 있음. 다만 마찬가지로 굳이 내림차순 한다면 코드만 봐도 오버헤드 상당히 증가
def qsort_cffi_array_in_place(arr: array.array):
    array_len = len(arr)
    addr, length = arr.buffer_info()            # 이게 array.array의 int* array, int size 를 불러오는 듯 함.

    start_ptr = ffi.cast("int *", addr)         # 대신, 자료형을 담는 방법이 list사용시와 약간 다름.
    end_ptr = start_ptr + length
    qsort.quick(start_ptr, end_ptr)             # type: ignore

    
def getRandList(sz:int) -> list:
    res = []
    for i in range(sz):
        res.append(random.randint(1, 10000))
    return res

#! 랜덤으로 만들기 위한 새로운 방법
def getRandList_fast(sz: int) -> list: 
    mask = 0x3FFF       # 16383
    raw = os.urandom(4 * sz)
    arr = struct.unpack(f"{sz}I", raw)
    # return [v & mask for v in arr]
    return [v % 10000 for v in arr]


def is_sorted(sorted:list, origin:list) -> bool:
    if len(sorted) != len(origin):
        return False
    origin.sort()
    return sorted == origin


def main():
    '''
    검사는 기본검사 / 벤치마크 이며, 자료형은 list, array.array 두가지가 사용된다.
    array.array 가 정렬에 압도적이나, list와의 전환 등에 시간이 꽤 걸림. getRandArray를 구현했었으나, 시간차 비슷함
    사실, list버전이 느리기보다는 복사시간때문에 시간이 증가한 것이라 생각됨. libqsort.so는 1억개의 배열(1~10000)을 2.8초 언저리로 정렬함
    정렬 신뢰검사는 합격했으며, 필요시 주석해제

    '''
    simple_test_sample_length = 15
    benchmark_sample_length = 100_000_000

    print("---기본검사---")
    sample = getRandList(simple_test_sample_length)
    print(sample)
    qsort_cffi(sample)
    print(sample)

    print("---기본검사2---")
    sample = array.array('i', getRandList(simple_test_sample_length))
    print(sample.tolist())
    qsort_cffi_array_in_place(sample)
    print(sample.tolist())
    


    print("---벤치마크---")
    bench_start = time.perf_counter()
    time_start = time.perf_counter()
    sample = getRandList_fast(benchmark_sample_length)
    cp = list(sample)
    print(f"배열생성시간: {time.perf_counter() - time_start}")

    time_start = time.perf_counter()
    qsort_cffi(cp)
    print(f"정렬소요시간: {time.perf_counter() - time_start}")

    # time_start = time.perf_counter()
    # b = is_sorted(cp, sample)
    # print(f"신뢰검증시간: {time.perf_counter() - time_start}")
    # print(f"정렬검증결과: {b}")
    print(f"총 소요시간: {time.perf_counter() - bench_start}")



    print("---벤치마크2---")
    bench_start = time.perf_counter()
    time_start = time.perf_counter()
    sample = array.array('i', getRandList_fast(benchmark_sample_length))
    cp = sample[:]
    print(f"배열생성시간: {time.perf_counter() - time_start}")

    time_start = time.perf_counter()
    qsort_cffi_array_in_place(cp)
    print(f"정렬소요시간: {time.perf_counter() - time_start}")

    # time_start = time.perf_counter()
    # b = is_sorted(cp.tolist(), sample.tolist())
    # print(f"신뢰검증시간: {time.perf_counter() - time_start}")
    # print(f"정렬검증결과: {'성공!' if b else '***실패***'}")    
    print(f"총 소요시간: {time.perf_counter() - bench_start}")
    return


if __name__ == "__main__":
    main()