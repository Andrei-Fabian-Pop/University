#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <string.h>

int main() {
	uint16_t port = 1234;
	char addr[] = "192.168.50.14";
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in client;
	client.sin_family = AF_INET;
	client.sin_port = htons(port);
	inet_aton(addr, &client.sin_addr);

	socklen_t clientlen = sizeof(client);

	connect(sock_fd, (const struct sockaddr *) &client, clientlen);

	char mess[] = "Lukaka\0";
	int l = strlen(mess);
	l = htons(l);
	write(sock_fd, &l, sizeof(int));
	write(sock_fd, mess, strlen(mess)+1);

	return 0;
}
