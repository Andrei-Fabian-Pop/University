from socket import*
import sys
import select

HOST = '192.168.0.119'
PORT = 1444
s = socket(family=AF_INET, type=SOCK_STREAM)
s.connect((HOST, PORT))

while True:
    socket_list = [sys.stdin, s]

    # Get the list sockets which are readable
    read_sockets, write_sockets, error_sockets = select.select(
        socket_list, [], [])

    for sock in read_sockets:
        #incoming message from remote server
        if sock == s:
            data = sock.recv(1024)
            if not data:
                print('\nDisconnected from server')
                break
            else:
                #print data
                sys.stdout.write(data)
                # prints the message received
                print("New message: " + repr(data))
                prompt()
        #user entered a message
        else:
            msg = sys.stdin.readline()
            s.send(msg)
            prompt()

s.close()
