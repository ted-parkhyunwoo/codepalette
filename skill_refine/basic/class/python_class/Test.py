# 기본클래스
class Test:
    def __init__(self, name:str = "null", age:int = 0):
        self.name:str = name
        self.age:int = age

    def userInit(self) -> None:
        # 입력 오류처리 없는 proto type.
        self.name = str(input("name: "))
        self.age = int(input("age: "))

    def init(self, name:str, age:int) -> None:
        self.name = name
        self.age = age

    def printInfo(self) -> None:
        print(f"name: {self.name}, age: {self.age}")


# 상속클래스
class Test2(Test):
    def __init__(self, name:str = "null", age:int = 0, phone:str = "000-0000-0000"):
        super().__init__(name, age)
        self.phone:str = phone
    
    # 경고무시. 매개변수가 같기를 기대함. 뒤에 주석도 경고 무시한다는 뜻
    #! 파이썬은 오버로딩을 원칙적으로 지원하지 않음. **kwargs 를 권장. **kwargs:키워드아규먼츠: 딕셔너리처럼 작동. *args: 아규먼츠: 튜플처럼 작동
    def init(self, name:str, age:int, phone:str) -> None: # type: ignore
        super().init(name, age)
        self.phone = phone

    def printInfo(self) -> None:
        print(f"name: {self.name}, age: {self.age}, phone: {self.phone}")
        

# 스태틱메서드를 포함한 클래스.
class Test3:
    @staticmethod
    def sayHello():
        print("Hello")

    @classmethod
    def sayWorld(cls):
        print("World")


