import socket

BUF_SIZE = 1024

while True:
    serv_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    ip = input("Input IP: ")  # set IP
    port = int(input("Input PORT: "))  # Set Port Number
    serv_addr = (ip, port)

    serv_sock.connect(serv_addr)  # Connect Server

    while True:
        send_data = input("Input Message: ")  # Input Send Message
        if send_data == 'q' or send_data == 'Q':  # If send message is 'q' or 'Q' -> Quit
            print(ip, "와의 접속을 종료 합니다.")
            serv_sock.send(send_data.encode())
            serv_sock.close()
            break
        else:
            serv_sock.send(send_data.encode())  # Send Message to Server
            recv_data = serv_sock.recv(BUF_SIZE).decode()  # Receive Message from Server

            if recv_data == 'q' or recv_data == 'Q':  # If received message is 'q' or 'Q' -> Quit
                print(ip, "와의 접속이 종료되었습니다.")
                serv_sock.close()
                break
            else:
                print("Server: ", recv_data)
