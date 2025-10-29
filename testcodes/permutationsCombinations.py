from pprint import pprint
from itertools import combinations, permutations

myList = [3, 1, 4, 1]

# 조합
combsRes = []
for t in combinations(myList, 2):
    combsRes.append(t)

# 순열
permuteRes = []
for t in permutations(myList, 2):
    permuteRes.append(t)

pprint(combsRes)
pprint(permuteRes)


#! 사이즈가 10까지(1기가 언저리)만 안전. 11은 매우느림. (10기가 언저리) 이상부터는 메모리 초과하여 시스템 정지됨
size = 9
test = []
for i in range(size):
    test.append(i)

testRes = []
for t in permutations(test, len(test) - 1):
    testRes.append(t)
print(testRes)
print(len(testRes))