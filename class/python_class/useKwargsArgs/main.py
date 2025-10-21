from myClass import myClass

test = myClass()

a = (1, 2, 3)
kw = {"a":1, "b":2, "c":3}

test.printArgs(*a)
test.printArgs(*(4,5,6))

# kwargs는 반드시 키가 문자열이어야 언패킹됨.
# json으로 저장한 설정이랑 찰떡 궁합처럼 사용될것으로 보임.
test.printKwargs(**kw)
test.printKwargs(**{"1":1})

