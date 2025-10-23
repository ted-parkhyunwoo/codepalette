from pprint import pprint
myList = [3, 1, 4, 1]

from itertools import combinations, permutations

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
