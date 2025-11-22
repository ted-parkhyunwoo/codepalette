
''' 
    ctypes 의 list->c array 전환은 gemini 도움을 받음
    기존의 코드(sort.py) 에서 퀵정렬 제외 가져옴.
    일부 코드가 원본(sort.py) 와 다르게 수정된 부분이 있음.
    cffi 를 사용한 정렬과 비교
    
'''

import random
import time
import ctypes
from ctypes import cdll, c_int, POINTER, sizeof
from cffi import FFI

PRINT_SORT_LOG:bool = False     #! sort_python_list 내부에 시간측정 프린트 여부
PRINT_TIME_DETAIL:bool = True  #! main의 3번검사(단일시간측정) 에서 '정렬시간 외' 배열 생성시간, 총소요시간 출력여부


#cffi용 선언
ffi = FFI()
#프로토타입같은 개념. h의 역할
ffi.cdef("""
    void quick(int* start, int* end);
""")
qsort = ffi.dlopen("./libqsort.so")



# ctypes로 선언
lib = cdll.LoadLibrary('./libqsort.so')
lib.quick.argtypes = [POINTER(c_int), POINTER(c_int)]
lib.quick.restype = None

def convert_pylist_to_c_int_array(py_list:list):
    c_int_array = c_int * len(py_list)
    c_int_array_result = c_int_array(*py_list)
    return c_int_array_result

def sort_python_list_ctypes(py_list, ascending:bool = True):
    arr_len = len(py_list)
    
    # Python list -> C style Array (int[])
    start_time = time.perf_counter()    
    c_arr = convert_pylist_to_c_int_array(py_list)           #! 전환

    start_ptr = c_arr 

    # end 지정이 c_arr + arr_len 처럼 작동되지 않음. 캐스팅((시작주소 + 인트사이즈*길이), 정수포인터타입)) 식으로 사용해야함.
    end_ptr = ctypes.cast((ctypes.addressof(c_arr) + sizeof(c_int) * arr_len), POINTER(c_int))
    
    # print(f"정렬 전: {list(c_arr)}")
    if PRINT_SORT_LOG: print(f"리스트->배열 완료: \t{time.perf_counter() - start_time} s")
    
    start_time = time.perf_counter()
    # C 함수 호출
    lib.quick(start_ptr, end_ptr)
    if PRINT_SORT_LOG: print(f"순수 C 정렬 시간: \t{time.perf_counter() - start_time} s")
    
    # 정렬된 C 배열을 다시 Python 리스트로 변환하여 출력
    start_time = time.perf_counter()
    res = []
    if ascending:
        res = list(c_arr)
    else:
        res = list(c_arr)[::-1]
    
    # 원본수정
    for i in range(arr_len):
        py_list[i] = res[i]
    if PRINT_SORT_LOG: print(f"배열->리스트 완료: \t{time.perf_counter() - start_time} s")

    return res


#! cffi 사용하여 정렬
def sort_python_list_cffi(py_list: list, s:bool = True) -> list:
    """
    Python 리스트를 CFFI 배열로 변환하여 C quick 함수를 호출하고 결과를 반환합니다.
    """
    array_len = len(py_list)

    # 1. Python 리스트를 C 배열로 변환 (메모리 할당 및 데이터 복사 발생)
    # "int[]" 타입에 py_list의 내용을 담아 새로운 C 배열을 생성합니다.
    c_arr = ffi.new("int[]", py_list)
    
    start_ptr = c_arr 
    end_ptr = c_arr + array_len 
    qsort.quick(start_ptr, end_ptr) # type: ignore  #! 이 주석 입력시 타입오류표기 해제
    res:list = ffi.unpack(c_arr, array_len) # type: ignore #! 이 주석 입력시 타입오류표기 해제

    if not s:
        res = res[::-1]

    for i in range(array_len):
        py_list[i] = res[i]

    return res



# 기존의 py 정렬
def _sort_insert(l:list, start:int, end:int, ascending:bool) -> None:
    # quick 등에서 사용할 index기반 삽입정렬
    for i in range(start + 1, end + 1):
        bf:int = l[i]
        j:int = i
        while j > 0 and (l[j - 1] > bf if ascending else l[j - 1] < bf):
            l[j] = l[j - 1]
            j -= 1
        if j != i:
            l[j] = bf

def _quick(l:list, start:int, end:int, ascending:bool) -> None:
    if (len(l) <= 1): return
    #! TEST 정렬전환
    if (end - start < 512):
        _sort_insert(l, start, end, ascending)
        return
    
    if start >= end: return
    # 분할
    left:int = start
    right:int = end
    pivot = l[start + int((end - start ) / 2)]

    while left <= right:
        while pivot > l[left] if ascending else pivot < l[left]: left += 1
        while pivot < l[right] if ascending else pivot > l[right]: right -= 1
        if (left <= right):
            l[left], l[right] = l[right], l[left]
            left += 1
            right -= 1
    # 정복
    if (start < right): _quick(l, start, right, ascending)
    if (end > left):    _quick(l, left, end, ascending)

def sort_quick(l:list, ascending:bool) -> None:
    _quick(l, 0, len(l) - 1, ascending)




# 헬퍼함수
# 랜덤배열 생성
def get_random_int_list(size:int, max:int) -> list[int]:
    res = []
    for i in range(size):
        res.append(random.randint(1, max))
    return res

# sort1과 sort2의 정렬시간 비교
def time_check_compare(sort1, sort2, size:int, max:int, loop:int,  printTask:bool = False) -> None:
    f1_sum = 0
    f2_sum = 0
    for _ in range(loop):
        arr:list = get_random_int_list(size, max)
        arr_cp: list = list(arr)
        
        f1_start = time.perf_counter()
        sort1(arr, True)
        f1_res = time.perf_counter() - f1_start

        arr_cp = list(arr)
        f2_start = time.perf_counter()
        sort2(arr_cp, True)
        # arr_cp.sort()     # 내장 기본 정렬 사용시 sort2주석처리 후 사용 : C 보다 빠름
        f2_res = time.perf_counter() - f2_start
        f1_sum += f1_res
        f2_sum += f2_res
        if (not printTask): print(f"loop {_ + 1}...")
        if (printTask): print("sort1: " + str(f1_res) + "  sort2: " +  str(f2_res))

    print(f"average sort1: {f1_sum / loop}  sort2: {f2_sum / loop}")

# 정렬됐는지 검사
def is_sorted(l:list, original:list, ascending:bool) -> bool:
    origin:list = list(original)
    if ascending: origin.sort()
    else: origin.sort(reverse= True)
    return l == origin

# 정렬됐는지 검사하고 출력
def printSortCorrectly(func, size:int = 10000):
    max:int = 1000

    arr:list = get_random_int_list(size, max)
    arr_cp:list = list(arr)
    asc: bool = True
    start = time.perf_counter()
    func(arr_cp, asc)
    restime = time.perf_counter() - start
    res = (is_sorted(arr_cp, arr, asc))
    print(f"{'오름차순' if asc else '내림차순'}: {'성공!' if res else '실패'} 소요시간: {restime}")    

    arr:list = get_random_int_list(size, max)
    arr_cp:list = list(arr)
    asc: bool = False
    start = time.perf_counter()
    func(arr_cp, asc)
    restime = time.perf_counter() - start
    res = (is_sorted(arr_cp, arr, asc))
    print(f"{'오름차순' if asc else '내림차순'}: {'성공!' if res else '실패'} 소요시간: {restime}")    


def main() :    


    # 단독 육안 테스트
    if True:
        sortfunc = sort_python_list_cffi

        sample:list = get_random_int_list(15, 50)
        cp_sample:list = list(sample)
        print("orig", end=": \t")
        print(sample)

        sortfunc(sample, True)
        # _sort_insert(sample, 0, len(sample)- 1, True)

        print(is_sorted(sample, cp_sample, ascending=True), end=": \t" )
        print(sample)
        sample = list(cp_sample)

        sortfunc(sample, False)
        # _sort_insert(sample, 0, len(sample)- 1, False)

        print(is_sorted(sample, cp_sample, ascending=False), end=": \t")
        print(sample)
    

    # 정렬검증
    if True    :
        sort_dict = {
            "quick": sort_quick, "C-qsort": sort_python_list_ctypes, "cffi-qsort": sort_python_list_cffi
        }

        for name in sort_dict.keys():
            print(f"{name} 시도: ")
            printSortCorrectly(sort_dict[name], 1000)



    # 단일 시간측정
    if True:
        bench_sort = sort_python_list_cffi
        sample_length = 100000000
        start_sample_make_time = time.perf_counter()
        single_bench_sample = get_random_int_list(sample_length, 10000)
        if PRINT_TIME_DETAIL: print(f"샘플 {sample_length}개 생성완료: \t{time.perf_counter() - start_sample_make_time} s")
        start_sorting = time.perf_counter()
        
        bench_sort(single_bench_sample, True)

        print(f"정렬 소요시간: \t{time.perf_counter() - start_sorting} s")
        if PRINT_TIME_DETAIL: print(f"샘플생성,정렬 총 소요시간: \t{time.perf_counter() - start_sample_make_time} s")


    # 소요시간 비교
    if True:
        sort1 = sort_python_list_ctypes
        sort2 = sort_python_list_cffi
        time_check_compare(sort1, sort2, 100_000_000, 10000, 1)
    
    return 0;

if __name__ == "__main__" :
    main()
