
''' 
    ctypes 의 list->c array 전환은 gemini 도움을 받음
    기존의 코드(sort.py) 에서 퀵정렬 제외 가져옴.
    일부 코드가 원본(sort.py) 와 다르게 수정된 부분이 있음.
    
'''

import random
import time
import ctypes
from ctypes import c_int, POINTER, cdll

PRINT_SORT_LOG:bool = False     #! sort_python_list 내부에 시간측정 프린트 여부
PRINT_TIME_DETAIL:bool = False  #! main의 3번검사(단일시간측정) 에서 '정렬시간 외' 배열 생성시간, 총소요시간 출력여부

try:
    lib = cdll.LoadLibrary('./libqsort.dll')        #!리눅스는 so로 하면 됨: gcc -fPIC -shared -O3 qsort.c -o libqsort.so
except OSError as e:
    print(f"오류: libqsort.dll 파일을 로드할 수 없습니다. 컴파일을 확인하세요. ({e})")
    exit()

# 2. C 함수 prototype 정의
# quick(int* start, int* end)
lib.quick.argtypes = [POINTER(c_int), POINTER(c_int)]
lib.quick.restype = None

def sort_python_list(py_list, ascending:bool = True):
    """
    Python 리스트를 C 배열 포인터로 변환하고 quick 함수를 호출합니다.
    """
    arr_len = len(py_list)
    
    # Python list -> C style Array (int[])
    start_time = time.perf_counter()
    C_INT_ARRAY = c_int * arr_len
    c_arr = C_INT_ARRAY(*py_list)           #! 전환
    
    # 포인터 계산
    # start 포인터: 배열의 첫 요소 주소
    start_ptr = c_arr 


    #! end 지정이 복잡함.
    # end 포인터: 배열의 마지막 요소 '다음' 주소 (배열의 크기만큼 오프셋)
    # ctypes.addressof(c_arr)로 배열의 시작 주소를 가져와서 오프셋을 더합니다.
    # POINTER(c_int) 타입으로 캐스팅하여 C 함수가 예상하는 형태로 전달합니다.
    end_ptr = ctypes.cast((ctypes.addressof(c_arr) + ctypes.sizeof(c_int) * arr_len), POINTER(c_int))
    
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



# 기존의 정렬

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
    if False:
        sortfunc = sort_python_list

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
    if False:
        sort_dict = {
            "quick": sort_quick, "C-qsort": sort_python_list
        }

        for name in sort_dict.keys():
            print(name)
            printSortCorrectly(sort_dict[name], 1000)



    # 단일 시간측정
    if True:
        bench_sort = sort_python_list
        sample_length = 100000000
        start_sample_make_time = time.perf_counter()
        single_bench_sample = get_random_int_list(sample_length, 10000)
        if PRINT_TIME_DETAIL: print(f"샘플 {sample_length}개 생성완료: \t{time.perf_counter() - start_sample_make_time} s")
        start_sorting = time.perf_counter()
        
        bench_sort(single_bench_sample, True)
        # single_bench_sample.sort()            # 기본정렬로 측정

        print(f"정렬 소요시간: \t{time.perf_counter() - start_sorting} s")
        if PRINT_TIME_DETAIL: print(f"샘플생성,정렬 총 소요시간: \t{time.perf_counter() - start_sample_make_time} s")


    # 소요시간 비교
    if False:
        sort1 = sort_python_list
        sort2 = sort_quick
        time_check_compare(sort1, sort2, 100_000_000, 10000, 1)
    
    return 0;

if __name__ == "__main__" :
    main()
