#1
from tabulate import tabulate
import os
from winner import Winner
from cards import Cards
from betting import Betting
import time

def clear():
#    os.system('cls' if os.name == 'nt' else 'clear')
    os.system('cls || clear')    
#승패 검사기, 게임 상태 저장
winner = Winner()
#카드덱, 각점수와 덱 관리.
cards = Cards()
#베팅 시스템
betting = Betting()

#* test. 승패 저장소.
total_result = []

# 상황 출력 생성: 진행 및 결과 변수저장 메서드
def score_display(option):
    if option == "status":
        status_table = {
            'Name': ['Dealer', "Player"],
            'Cards': [(f"*   {cards.getDeck('dealer','cards')[1]}"), ('  '.join(cards.getDeck('player','cards')))],
            'Score': [(f"[* , {cards.getDeck('dealer','score')[1]}]"), cards.getDeck('player','score')],
            'Current Score': [(f"at least {cards.getDeck('dealer','score')[1]}"), cards.getTotalScore('player','total')],
            }
        
        print(tabulate(status_table, headers='keys', tablefmt="pretty"))

    elif option == "result":
        result_table = {
            'Name': ['Dealer', "Player"],
            'Cards': [('  '.join(cards.getDeck('dealer','cards'))), ('  '.join(cards.getDeck('player','cards')))],
            'Score': [cards.getDeck('dealer','score'), cards.getDeck('player','score')],
            'Status' : [winner.status_dealer , winner.status_player],
            'Total': [cards.getTotalScore('dealer','total'), cards.getTotalScore('player','total')]
            }
        
        print(tabulate(result_table, headers='keys', tablefmt="pretty"))
    print(f"remaining {cards.getCardInfo('cards','remain')} cards. used {cards.getCardInfo('cards','decks')} deck(s).")


# 한 턴의 진행
def main():
    
    # 해당게임 결과출력 함수정의. 
    def show_result():
        winner.result(cards.getTotalScore('dealer','total'), cards.getTotalScore('player','total'), len(cards.getDeck('dealer','cards')), len(cards.getDeck('player','cards')))
        score_display("result")
        
    # hit or stand 루프 탈출 변수 false 선언    
    gameover = False
    
    # 초기 카드배분(4장)
    for deal in range(2):
        cards.deal_card("player")
        cards.deal_card("dealer")

    # 초기 배분 bust발생시 ace->1점 처리.
    if cards.getTotalScore('player','total') > 21:
        cards.ace_changer("player")
    if cards.getTotalScore('dealer','total') > 21:
        cards.ace_changer("dealer")

    # 진행 상황 출력(딜러 *마스킹처리.)
    score_display("status")
    
    #! 테스트용 타입 슬립.
    time.sleep(0.5)

    # 초기배분 플레이어 블랙잭 체크.(규칙상 플레이어 블랙잭에서만 hit or strand로 진행하지 않으므로.)  
    if cards.getTotalScore('player','total') == 21:
        clear()
        
        #결과 생성/출력
        show_result()
        gameover = True

    # hit or stand 루프.
    while not gameover:
        hit_stand = input("Hit = (H) , Stand = (Enter) : ").lower()
        
        # stand(종료)
        if hit_stand == "":
            clear()
            cards.dealer_16()      
              
            #결과 생성/출력
            show_result()
            gameover = True

        # hit(플레이어 카드 이어받기)
        elif hit_stand == "h":
            clear()
            cards.deal_card("player")

            # hit중 bust시 ace->1 우선 처리
            if cards.getTotalScore('player','total') > 21:
                cards.ace_changer("player")
            
            # bust, 21달성시 결과생성/출력
            if cards.getTotalScore('player','total') > 21 or cards.getTotalScore('player','total') == 21:        
                
                #결과 생성/출력
                show_result()
                gameover = True

            # hit or stand 루프 재진입
            else:
                score_display("status")
                              
        # 이외 입력 hit or stand 입력 검사기 처리
        else:
            print("Please type only 'h' or 'enter'")


#세이브파일 로드. (최초 1회 실행 위해 반복문 밖에 사용.)
betting.load_bank()

# stop 입력 전까지 턴 루프.
play_again = True
while play_again:
    
    # 잔고 프린트, 새 베팅 진행과 검사.
    print(f"Bank : ${betting.bank}")
    bet_checker = True
    while bet_checker:
        if betting.bet_amount() == True:
            bet_checker = False
    
    #한 턴 진행.
    main()
    
    # 보수 정산 전 타임슬립.
    time.sleep(0.5)
    
    # 베팅보수 정산.
    betting.settlement(winner.game_result)
    
    # 세이브파일 생성.
    betting.save_bank()

    #* test. 토탈 과정 리스트 저장과 출력.  - 다듬어야함.
    total_result.append(winner.game_result)
    print(total_result[-1])
    
    # bank 고갈시 자동 종료.
    if betting.bank <= 0:
        print(f"You have no money. Game Over.")
        
        #todo. 종료 출력 손보기.
        time.sleep(0.5)
        print(total_result)
        print(f"Last : ${betting.bank}, Highest : ${betting.highest}")
        play_again = False
        break
    
    # 턴 재진입 
    result = input("Try again? ('stop' to exit) : ").lower()
    # stop 시 총 결과 정산,출력
    if result == "stop":
        
        print("Game over.")
        betting.save_bank()
        print("Bank data saved.")

        #todo. 종료 출력 손보기.
        time.sleep(0.5)
        print(total_result)        
        print(f"Last : ${betting.bank}, Highest : ${betting.highest}")       
        play_again = False
        
    # 새로운 턴 시도시 최근 정보 초기화.
    else:
        clear()
        cards.clear_decks()
        winner.clear_status()
