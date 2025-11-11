import time
import random

class sort():
    def __init__(self, array):
        self.original = array;
        self.SIZE = len(self.original)
        self.result = []
    
    def clearResult(self):
        self.__init__(self.original)

    def bubble(self):
        self.result = list(self.original)
        for i in range(self.SIZE - 1):
            for j in range(self.SIZE - i - 1):
                if self.result[j] > self.result[j + 1]:     self.result[j], self.result[j + 1] = self.result[j + 1], self.result[j] 

    def select(self):
        self.result = list(self.original)
        for i in range(self.SIZE):
            minIdx:int = i
            for j in range(i, self.SIZE):
                if self.result[j] < self.result[minIdx]:        minIdx = j
            if minIdx != i:     self.result[i], self.result[minIdx] = self.result[minIdx], self.result[i]

    def insert(self):
        self.result = list(self.original)
        for i in range(1, self.SIZE):
            buffer = self.result[i]
            j:int = i
            while j > 0 and self.result[j - 1] > buffer:
                self.result[j] = self.result[j - 1];
                j -= 1
            if j != i:          self.result[j] = buffer;

    def shell(self):
        self.result = list(self.original)
        gap:int = int(self.SIZE / 2)
        while (gap > 0) :
            i:int = gap
            while i < self.SIZE:
                buffer = self.result[i]
                j:int = i
                while j >= gap and self.result[j - gap] > buffer:
                    self.result[j] = self.result[j - gap]
                    j -= gap
                if j != i:      self.result[j] = buffer
                i += 1
            gap = int(gap / 2)

    # 모두 테스트
    def do_test(self):
        funcs:list = [self.bubble, self.select, self.insert, self.shell]
        res:list = []
        for func in funcs:
            start= time.time()
            func()
            end = time.time()
            res.append(end - start)
        print(res)
            

myArray = [ 2, 3, 7, 1, 9, 6, 0, 5, 4, 8 ]

testInstance = sort(myArray)
testInstance.bubble()
print(testInstance.result)

testInstance.select()
print(testInstance.result)

testInstance.insert()
print(testInstance.result)

testInstance.shell()
print(testInstance.result)


# 모두 테스트 하여 시간계산(python은 삽입이 선택보다 느리게 나옴: 코드에 문제는 없지만, python에서 swap"a,b = b,a"보다 옮기는 것"참조재할당"이 비용이 큼.)
data_list = random.sample(range(1, 100001), 10000)
time_check = sort(data_list)
time_check.do_test()