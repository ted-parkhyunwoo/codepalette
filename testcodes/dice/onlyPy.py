import random
import time

class dice:
    def __init__(self):
        self.count:list = [0 for _ in range(6)]

    @staticmethod
    def getDice() -> int:
        return random.randint(1, 6)

    def roll(self, num:int) -> None:
        for _ in range(num):
            a = self.getDice()
            self.count[a - 1] += 1;

    def desc(self):
        for i in range(6):
            print(f"{i + 1}: {self.count[i]}")


a = time.time()
d = dice()
d.roll(100000000)
d.desc()
b = time.time()

print(b - a)
