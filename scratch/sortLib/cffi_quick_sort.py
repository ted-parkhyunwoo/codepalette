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

qsort = ffi.dlopen("./lib/libqsort.so")

# list를 이용한 cffi버전 quick: 매개변수를 직접 수정할 수 없어 아래 for문으로 요소 모두 재할당 (메모리 오버헤드 증가. 함수 실행시간 상승)
def qsort_cffi(py_list: list) -> None:
    array_len = len(py_list)    
    c_arr = ffi.new("int[]", py_list)           # c_arr = int[]자료형에 py_list를 담음
    start_ptr = c_arr                           # start_ptr, end_ptr 선언은 쉬운편
    end_ptr = c_arr + array_len 

    start_time = time.perf_counter()
    qsort.quick(start_ptr, end_ptr)             # type: ignore
    res_time = time.perf_counter()
    print(f"실질적인 정렬시간: {'{:.10f}'.format(res_time - start_time)}")

    res:list = ffi.unpack(c_arr, array_len)     # type: ignore

    for i in range(array_len):
        py_list[i] = res[i]


# array.array를 이용한 cffi버전 quick : list 처럼 내부에 복사할 필요 없이 원본을 수정할 수 있음. 대신 할당 자체가 걸리는편.
def qsort_cffi_array_in_place(arr: array.array):
    array_len = len(arr)
    addr, length = arr.buffer_info()            # 이게 array.array의 int* array, int size 를 불러오는 듯 함.

    start_ptr = ffi.cast("int *", addr)         # 대신, 자료형을 담는 방법이 list사용시와 약간 다름.
    end_ptr = start_ptr + length
    start_time = time.perf_counter()
    qsort.quick(start_ptr, end_ptr)             # type: ignore
    res_time = time.perf_counter()
    print(f"실질적인 정렬시간: {'{:.10f}'.format(res_time - start_time)}")    
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
    검사: 기본검사 / 벤치마크
    자료형: list / array.array

    '''
    simple_test_sample_length = 15
    benchmark_sample_length = 100_000_000

    if True:
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
    

    # 주석은 정렬검증에 관한 내용. 필요시 해제
    if True:
        print("---벤치마크---")
        bench_start = time.perf_counter()
        time_start = time.perf_counter()
        sample = getRandList_fast(benchmark_sample_length)
        # cp = list(sample)
        print(f"배열생성시간: {time.perf_counter() - time_start}")

        time_start = time.perf_counter()
        qsort_cffi(sample)
        print(f"함수소요시간: {time.perf_counter() - time_start}")

        time_start = time.perf_counter()
        # b = is_sorted(sample, cp)
        # print(f"신뢰검증시간: {time.perf_counter() - time_start}")
        # print(f"정렬검증결과: {'성공!' if b else '***실패***'}")    
        print(f"총 소요시간: {time.perf_counter() - bench_start}")



        print("---벤치마크2---")
        bench_start = time.perf_counter()
        time_start = time.perf_counter()
        sample = array.array('i', getRandList_fast(benchmark_sample_length))
        # cp = sample[:]
        print(f"배열생성시간: {time.perf_counter() - time_start}")

        time_start = time.perf_counter()
        qsort_cffi_array_in_place(sample)
        print(f"함수소요시간: {time.perf_counter() - time_start}")

        time_start = time.perf_counter()
        # b = is_sorted(sample.tolist(), cp.tolist())
        # print(f"신뢰검증시간: {time.perf_counter() - time_start}")
        # print(f"정렬검증결과: {'성공!' if b else '***실패***'}")    
        print(f"총 소요시간: {time.perf_counter() - bench_start}")

    return

if __name__ == "__main__":
    main()