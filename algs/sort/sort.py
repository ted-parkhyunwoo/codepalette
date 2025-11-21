import random
import time

# 정렬함수

def sort_bubble(l:list, ascending:bool) -> None:
    sz:int = len(l);
    for i in range(0, sz - 1):
        for j in range(0, sz - i - 1):
            cond:bool = l[j] > l[j + 1] if ascending else l[j] < l[j + 1]
            if cond:
                l[j], l[j + 1] = l[j + 1], l[j]

def sort_select(l:list, ascending:bool) -> None:
    sz:int = len(l)
    for i in range(0, sz):
        minIdx:int = i
        for j in range(i, sz):
            cond:bool = l[minIdx] > l[j] if ascending else l[minIdx] < l[j]
            if cond:
                l[minIdx], l[j] = l[j], l[minIdx]

def sort_insert(l:list, ascending:bool) -> None:
    sz:int = len(l)
    for i in range(1, sz):

        bf:int = l[i]
        j:int = i

        ## for문버전은 j = k - 1이 관건. c처럼 for문 내 조건(j혹은 k가 증감 하기 전 평가)이 range로 뿌리는거랑 다르다는 점을 인지.
        # for k in range(i, 0, -1):
        #     cond:bool = l[k - 1] > bf if ascending else l[k - 1] < bf
        #     if cond:
        #         l[k] = l[k - 1]
        #         j = k - 1
        #     else: break
        # if j != i:
        #     l[j] = bf

        while j > 0 and (l[j - 1] > bf if ascending else l[j - 1] < bf):
            l[j] = l[j - 1]
            j -= 1
        if j != i:
            l[j] = bf

def sort_shell(l:list, ascending:bool) -> None:
    sz:int = len(l)
    gap:int = 1
    while (gap < sz / 3):
        gap = gap * 3 + 1
    while(gap > 0):
        sz:int = len(l)
        for i in range(gap, sz):

            bf:int = l[i]
            j:int = i

            while j >= gap and (l[j - gap] > bf if ascending else l[j - gap] < bf):
                l[j] = l[j - gap]
                j -= gap
            if j != i:
                l[j] = bf
        gap = int(gap / 3)

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


def sort_merge(l:list, ascending:bool = True) -> None:
    # 분할
    a_size:int = len(l)
    if (a_size <= 1): return

    if (a_size <= 64):
        sort_insert(l, ascending)
        return
    
    left_size:int = int(a_size / 2)
    right_size:int = a_size - left_size
    left_list:list = l[:left_size]
    right_list:list = l[left_size:]

    # 정복
    sort_merge(left_list, ascending)
    sort_merge(right_list, ascending)

    # 합병(하면서 정렬)
    idx_buffer_dict = {"left": 0, "right": 0, "result" : 0}
    def _merge(type:str):
        if type == "left":
            l[idx_buffer_dict["result"]] = left_list[idx_buffer_dict["left"]] 
            idx_buffer_dict["left"] += 1 
        elif type == "right":                           
            l[idx_buffer_dict["result"]] = right_list[idx_buffer_dict["right"]]
            idx_buffer_dict["right"] += 1
        else: return
        idx_buffer_dict["result"] += 1

    while (idx_buffer_dict["left"] < left_size) and (idx_buffer_dict["right"] < right_size):
        cond:bool = left_list[idx_buffer_dict["left"]] > right_list[idx_buffer_dict["right"]]
        if ascending: cond = not cond
        if (cond):                      _merge("left")
        else:                           _merge("right")

    # 찌꺼기 처리 (위 루프에서 둘다 끝날 수도 있지만, 남더라도 한쪽만 남았으므로(이전 정복:재귀 에서 정렬됨) 나머진 자동 채워넣기)
    while idx_buffer_dict["left"] < left_size:          _merge("left")
    while idx_buffer_dict["right"] < right_size:        _merge("right")



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
        sortfunc = sort_quick

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
            "bubble": sort_bubble, "select": sort_select, "insert": sort_insert, "shell": sort_shell, "merge": sort_merge, "quick": sort_quick
        }

        for name in sort_dict.keys():
            print(name)
            printSortCorrectly(sort_dict[name], 1000)



    # 단일 시간측정
    if False:
        bench_sort = sort_merge
        single_bench_sample = get_random_int_list(100000000, 10000)
        print("샘플생성완료. 정렬중...")
        start = time.perf_counter()
        
        bench_sort(single_bench_sample, True)
        # single_bench_sample.sort()            # 기본정렬로 측정

        print(time.perf_counter() - start)


    # 소요시간 비교
    if True:
        sort1 = sort_merge
        sort2 = sort_quick
        time_check_compare(sort1, sort2, 1000000, 10000, 3)
    
    return 0;

if __name__ == "__main__" :
    main()
