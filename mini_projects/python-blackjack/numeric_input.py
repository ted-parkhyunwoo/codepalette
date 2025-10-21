class NumericInput:
    
    #Todo. betting과 cards(덱 선택) 두가지에 쓰이는데, betting엔 float가 쓰일 수 있으니 로직 수정 고려.
    #Todo. 현재 함수는 str, float 등 여러가지 타입으로 리턴되고있음.
    def get_numeric(self, prompt:str="input: ") -> str:
        while True:
            user_input = input(prompt)
            try:
                # 현 블랙잭 게임의 추가 로직. 베팅과 카드덱에서 빈 값 입력시 그대로 return.
                if user_input == "":
                    # print("No input detected.")
                    return ""
                numeric_value = user_input
                return numeric_value
            except ValueError:
                print("Please type only number.")


#현재 "" 입력시 그대로 return되니 이 코드는 재사용시 수정 필요함.