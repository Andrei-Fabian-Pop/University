import socket
import random

host = "127.0.0.1"
port = 9999

x = random.randint(0, 100)
y = random.randint(0, 100)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client:
    client.connect((host, port))

    client.send(str((x, y)).encode())

    print(client.recv(1024).decode())

    client.close()
