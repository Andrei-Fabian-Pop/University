import socket
import random
from math import sqrt

host = "127.0.0.1"
port = 9999

x = random.randint(0, 100)
y = random.randint(0, 100)


def calc_dist(a, b):
    global x, y
    return sqrt((x - a) * (x - a) + (y - b) * (y - b))


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
    server.bind((host, port))
    server.listen(7)

    conn1, addr1 = server.accept()
    x1, y1 = eval(conn1.recv(1024).decode())

    conn2, addr2 = server.accept()
    x2, y2 = eval(conn2.recv(1024).decode())

    conn3, addr3 = server.accept()
    x3, y3 = eval(conn3.recv(1024).decode())

    d1 = calc_dist(x1, x1)
    d2 = calc_dist(x2, x2)
    d3 = calc_dist(x3, x3)

    mx = max(d1, d2, d3)

    if d1 == max(d1, d2, d3):
        conn1.send("You won".encode())
    else:
        conn1.send("You lost".encode())

    if d2 == max(d1, d2, d3):
        conn2.send("You won".encode())
    else:
        conn2.send("You lost".encode())

    if d3 == max(d1, d2, d3):
        conn3.send("You won".encode())
    else:
        conn3.send("You lost".encode())

    print(f"generated: x={x}, y={y}\n"
          f"con 1: x={x1}, y={y1}, d={d1}\n"
          f"con 2: x={x2}, y={y2}, d={d2}\n"
          f"con 3: x={x3}, y={y3}, d={d3}")

    server.close()
