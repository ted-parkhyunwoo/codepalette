from Test import Test
from Test import Test2
from Test import Test3

tInstance = Test()
# 접근제한자 처리 없음.
tInstance.age = 3;
tInstance.name = "kim";
tInstance.printInfo()

t2Instance = Test()
t2Instance.init("park", 2)
t2Instance.printInfo()

# 기본매개변수를 통해 오버로딩같은 효과를 줄 순 있음.
t3Instance = Test("lee", 30)
t3Instance.printInfo()


# 상속클래스
derived = Test2(name="ted", age=29, phone="010-1010-2020")
derived.printInfo()

derived2 = Test2()
derived2.init("park", 27, "010-1234-5678")
derived2.printInfo()


#스태틱 메서드/클래스매서드 : 인스턴스 생성 없이 바로사용

#스태틱메서드
Test3.sayHello()
#클래스메서드
Test3.sayWorld()
