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