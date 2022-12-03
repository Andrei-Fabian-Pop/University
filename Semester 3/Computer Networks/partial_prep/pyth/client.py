from socket import socket, AF_INET, SOCK_STREAM

def client():
	sk = socket(family=AF_INET, type=SOCK_STREAM)
	sk.connect(("172.30.116.229", 1234))

	while True:
		message = input('c-> ')
		sk.send(message.encode())
		
		data = sk.recv(1024).decode()
		print("S -> " + data)
	sk.close()

if __name__ == '__main__':
	client()
