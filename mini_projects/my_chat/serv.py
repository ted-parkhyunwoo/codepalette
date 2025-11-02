import socket
import threading

IP = '127.0.0.1'
PORT = 5001

clients = []  # 연결된 클라이언트 소켓 목록

def broadcast(msg, sender_conn):
    # 보낸 사람을 제외한 모든 클라이언트에게 메시지 전송
    for client in clients:
        if client != sender_conn:
            try:
                client.send(msg.encode('utf-8'))
            except:
                clients.remove(client)
                client.close()

def handle_client(conn, address):
    print(f"new connect: {address[0]}")
    clients.append(conn)

    while True:
        data = conn.recv(1024)
        if not data:
            break
        user_msg = data.decode('utf-8')
        res_msg = f"{address[0]}: {user_msg}"
        print(res_msg)

        if user_msg == '!quit':
            break

        broadcast(res_msg, conn)  # 메시지를 다른 클라이언트에게 전달

    conn.close()
    clients.remove(conn)

# 서버 소켓 생성 및 대기 시작
sock = socket.socket()
sock.bind((IP, PORT))
sock.listen()
print("Server is listening")

# 클라이언트 연결 수락 및 스레드로 처리
while True:
    conn, addr = sock.accept()
    threading.Thread(target=handle_client, args=(conn, addr)).start()
