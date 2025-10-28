# 객체를 생성하여 작동.
class Bubble():
    def __init__(self, array:list) -> None:
        self.array:list = list(array)        # shallow copy.
        self.swapCount:int = 0;

    def swapValue(self, aIdx, bIdx) -> None:
        self.array[aIdx], self.array[bIdx] = self.array[bIdx], self.array[aIdx]
        self.swapCount += 1;
    
    def bsort(self) -> None:
        sz:int = len(self.array)
        for i in range(sz - 1):
            swapped:bool = False
            for j in range(sz - 1 - i):
                left = self.array[j]
                right = self.array[j + 1]
                if (left > right):
                    self.swapValue(j, j + 1)
                    swapped = True
            if not swapped:
                break


# void 함수처럼 작동. 실행하면 원본을 수정.
class autoBubble():
    def __init__(self, array) -> None:
        self.array = array
        self.bsort()

    def bsort(self) -> None:
        sz:int = len(self.array)
        for i in range(sz - 1):
            swapped:bool = False
            for j in range(sz - 1 - i):
                if (self.array[j] > self.array[j + 1]):
                    self.array[j], self.array[j +1] = self.array[j + 1], self.array[j]
                    swapped = True
            if not swapped:
                break


testArray = [3, 1, 2, 5, 6, 7, 2, 3, 54, 12]
myInstance = Bubble(testArray)
myInstance.bsort()
print(myInstance.array)
print(myInstance.swapCount)
print(testArray)        # 원본 보존.

r = [3, 1, 2, 5, 6, 7, 2, 3, 54, 12]
autoBubble(r)
print(r)