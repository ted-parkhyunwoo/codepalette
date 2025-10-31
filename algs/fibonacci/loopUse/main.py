import ctypes
import os

fib_lib = os.path.join(os.getcwd(), "libfib.so")
fib = ctypes.CDLL(fib_lib)

fib.getFib.argtypes = [ctypes.c_int]
fib.getFib.restype = ctypes.c_ulonglong

for i in range(94):
    print(f"{i}: {fib.getFib(i)}")

print("BYE")
