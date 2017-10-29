import socket

BUF_SIZE = 1024

IP = socket.gethostbyname(socket.gethostname())  # Set current IP
port = int(input("PORT: "))  # Input & Set Port number
serv_addr = (IP, port)

serv_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # IPv4, TCP

serv_sock.bind(serv_addr)  # Set IP, PORT number

serv_sock.listen(1)

while True:
    clnt_sock, clnt_addr = serv_sock.accept()  # Accept any Client
    print("Connected from ", clnt_addr)

    while True:
        data = clnt_sock.recv(BUF_SIZE).decode()  # Receive from Client
        if data == 'q' or data == 'Q':  # If received message is 'q' or 'Q' -> Quit
            print(clnt_addr, "와의 접속 종료되었습니다.")
            clnt_sock.close()
            break
        else:
            print("Client: ", data)
            send_data = input("Input Message: ")  # Input send message
            if send_data == 'q' or send_data == 'Q':  # If send message is 'q' or 'Q' -> Quit
                print(clnt_addr, "와의 접속 종료")
                clnt_sock.send(send_data.encode())
                clnt_sock.close()
                break
            else:
                clnt_sock.send(send_data.encode())  # Send message to Client
