import socket

host = "127.0.0.1"
port = 9999

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as client:
    client.sendto("Hello from cli".encode(), (host, port))
    rec = client.recvfrom(1024)
    message = rec[0].decode()
    addr = rec[1]
    print(f"Server {addr} sent {message}")
