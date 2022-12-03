import socket
import select
# readable,_,_ = select.select(clients, [], clients)

def server():
	sk = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM) # SOCK_DGRAM 
	sk.bind(('172.30.116.229', 1234))
	sk.listen(7)
	conn, addr = sk.accept()
	print("Connection from: " + str(addr))

	while True:
		data = conn.recv(1024).decode()
		# print(type(data))
		if not data:
			break
		print("Received: " + data)
		
		data = input('s-> ')

		conn.send(data.encode())
	
	conn.close()
	sk.close()

if __name__ == '__main__':
	server()
