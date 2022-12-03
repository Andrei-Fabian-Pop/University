import socket

host = "127.0.0.1"
port = 9999

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect((host, port))

    ms = "[i for i in range(0, 10, 2)]"

    sock.send(str(ms).encode())

    print(sock.recv(1024).decode())
