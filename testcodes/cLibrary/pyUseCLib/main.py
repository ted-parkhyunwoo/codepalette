import ctypes
import os

# c라이브러리 객체초기화
mylibPath = os.path.join(os.getcwd(), "libmylib.so")    # os.path.join은 현재os에 맞게 경로 합쳐줌(\ 혹은 /로.) getcwd() 는 작업경로
mylib = ctypes.CDLL(mylibPath)                          # CDLL은 so, dll(win)을 로드.

# 멤버함수 타입정의
mylib.arraySum.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_size_t]
mylib.arraySum.restype = ctypes.c_int
mylib.printWelcome.argtypes = [ctypes.c_char_p]
mylib.printWelcome.restype = None                       # void 리턴은 생략가능. None으로 명시

# python 변수
py_list =  [1, 2, 3, 4, 5]
py_name = "ted"

# ctype에 맞게 변수 재가공
c_arr = (ctypes.c_int * len(py_list))(*py_list)
c_name = py_name.encode()

# 사용
print(mylib.arraySum(c_arr, len(py_list)))
mylib.printWelcome(c_name)

