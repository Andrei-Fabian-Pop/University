import socket

host = "127.0.0.1"
port = 9999

# broadcast
# host = socket.INADDR_ANY

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as server:
    server.bind((host, port))

    while True:
        rec = server.recvfrom(1024)
        message = rec[0].decode()
        addr = rec[1]
        print(f"{addr} sent {message}")

        server.sendto("Message received".encode(), addr)
