import ctypes
import os
import time
from datetime import timedelta

# 라이브러리로 free호출 준비과정
from ctypes.util import find_library
libc_path = find_library("c")
libc = ctypes.CDLL(libc_path)
libc.free.argtypes = [ctypes.c_void_p]



libPath = os.path.join(os.getcwd(), "libprime.so")
lib = ctypes.CDLL(libPath)

lib.get.argtypes = [ctypes.c_size_t]
lib.get.restype = ctypes.POINTER(ctypes.c_size_t)

test = 1000000000

timeStart = time.time()
c_ptr = lib.get(test)
print(c_ptr[0])
timeEnd = time.time()

timeRes = timedelta(seconds=(timeEnd - timeStart))
print(timeRes)

# for i in range(1, c_ptr[0] + 1):
#     print(i, c_ptr[i])




# libc의 free호출
#libc.free(c_ptr)

# 내장함수로 호출
lib.freeMem(c_ptr)
