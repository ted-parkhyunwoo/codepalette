import socket
import threading

IP = '127.0.0.1'
PORT = 5001

# 서버에 연결
sock = socket.socket()
sock.connect((IP, PORT))

# 쓰레드 종료 트리거
stop_thread = False

# 서버로부터 메시지를 수신하는 쓰레드
def receive():
    global stop_thread
    while not stop_thread:  # 기저조건 체크
        try:
            data = sock.recv(1024)
            if not data:
                break
            print(data.decode('utf-8'))
        except:
            break
    print("Receiver thread stopped.")

# 수신 쓰레드 시작
thread = threading.Thread(target=receive, daemon=True)  #! deamon은 백그라운드에서 실행되도록 함 (따라서 stop_thread같은 종료 기저조건이 필요.)
thread.start()

# 메시지 입력 및 전송 루프
while True:
    msg = input()  # 사용자 입력
    sock.send(msg.encode("utf-8"))
    print(f"YOU: {msg}")  # 출력

    if msg == '!quit':  # 종료 명령
        stop_thread = True
        break

thread.join()  # 쓰레드 종료 대기
sock.close()  # 소켓 닫기
print("Socket closed and program terminated.")