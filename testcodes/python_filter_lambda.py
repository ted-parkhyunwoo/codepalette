def odd(n):
    if n % 2 == 0:
        return False
    return True

def prime(n):
    if n <= 1:
        return False
    for e in range(2, n):
        if n % e == 0:
            return False
    return True


print("Filter Test:")

oddlist = list(filter(odd, range(10)))
print(oddlist)

primeList = list(filter(prime, range(100)))
print(primeList)


print("\nLambda Filter Test: ")
# even: not odd, arr 식으로 필터를 쓸 수 없으니, even함수를 새로 작성하거나, 램다로 적용함.
evenlist = list(filter(lambda n: not odd(n) and n != 0, range(100)))
print(evenlist)

# 복합 (홀수 이면서 5의 배수가 아님)
odd_and_not_multiple_of_five = list(filter(lambda n: odd(n) and n % 5 != 0, range(100)))
print(odd_and_not_multiple_of_five)

# 369게임 에서 뽑히면 안되는수
tsn = list(filter(lambda n: '3' not in str(n) and '6' not in str(n) and '9' not in str(n), range(1, 101)))
print(tsn)



# lambda의 매개변수가 두개일 수 있음
t = (lambda a, b: a + b)(1, 2)      # 1, 2를 즉시적용
print(t)

test = map(lambda a, b: a + b, range(5), range(3)) # [0, 1, 2, 3, 4] + [0, 1, 2] = [0, 2, 4]
print(list(test))
