import ctypes
import os
import time

data_lib_path = os.path.join(os.getcwd(), "libdata.so")
data_lib = ctypes.CDLL(data_lib_path)


C_LONG_TYPE = ctypes.c_longlong

class data(ctypes.Structure):
    _fields_ = [("count", C_LONG_TYPE * 6)]

data_lib.initData.argtypes = [ctypes.POINTER(data)]
data_lib.descData.argtypes = [ctypes.POINTER(data)]
data_lib.plusElement.argtypes = [ctypes.POINTER(data), ctypes.c_uint]

mydata = data()
data_lib.initData(ctypes.byref(mydata))
data_lib.descData(ctypes.byref(mydata))

import random

a = time.time()
for i in range(100000000):
    data_lib.plusElement(ctypes.byref(mydata), random.randint(1,6))

b = time.time()

data_lib.descData(ctypes.byref(mydata))
print(b - a)