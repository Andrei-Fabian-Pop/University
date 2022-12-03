import socket
import threading

host = "127.0.0.1"
port = 9999

num = 0
lock = threading.Lock()


def treat_client(sk):
    data = eval(sk.recv(1024).decode())
    print(data)

    lock.acquire()
    n = num
    lock.release()

    conn.send(f"You are nr {n}".encode())


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.bind((host, port))
    sock.listen(7)

    while True:
        conn, addr = sock.accept()

        with conn:
            print("Connected by " + str(addr))

            thr = threading.Thread(target=treat_client, args=(conn,))

            lock.acquire()
            num = num + 1
            lock.release()
            thr.start()
            thr.join()
