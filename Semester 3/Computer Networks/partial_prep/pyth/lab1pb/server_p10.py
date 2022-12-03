# 10.The client sends to the server two strings. The server sends back the character with the largest number of
# occurrences on the same positions in both strings together with its count.

import socket


def main():
    # str1 = "This is string one"
    # str2 = "This is string two"

    sk = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)
    sk.bind(('172.30.116.229', 9999))
    sk.listen(7)

    conn, addr = sk.accept()

    while True:
        str1 = conn.recv(1024).decode()
        str2 = conn.recv(1024).decode()
        if not str1 or not str2:
            print("At least one string is empty")
            break

        dc = {}
        for i in range(min(str1.len(), str2.len())):
            if str1[i] == str2[i]:
                if str1[i] not in dc.keys():
                    dc[str1[i]] = 1
                else:
                    dc[str1[i]] += 1


if __name__ == "__main__":
    main()
