import ctypes
import os

#! 피보나치를 재귀식으로 쓰면 할당과 해제 관리 등 코드도 복잡하고 오버헤드가 증가함. 


fibPath = os.path.join(os.getcwd(), "libfibonacci.so")  # getcwd = get current working directory
fib_lib = ctypes.CDLL(fibPath)

fib_lib.getFib.argtypes = [ctypes.c_int]
fib_lib.getFib.restype = ctypes.c_ulonglong

def getFib(n: int) -> int: # return type: unsigned long long int -> int(python)
    res = fib_lib.getFib(n)
    return res

def getFibRange(start:int, end:int) -> None:
    #! 92 이상 예외처리 추가하지 않으면 C에서 강제종료 예외처리되므로, 파이썬이 제외권 상실함. print("BYE") 출력이 안됨.
    if end > 92:    
        print("Warning: 92 이상을 쓸 수 없음.")
        end = 92
    for i in range(start, end):
        print(fib_lib.getFib(i))



#! 메모리를 함수 내에서 관리하면 각 할당과 해제 등이 여러번 일어날 수 있다며 파이썬에서 실행 불가.
fib_lib.initMemo(100)
print(getFib(92))
getFibRange(0, 100)
fib_lib.freeMemo()


print("BYE")