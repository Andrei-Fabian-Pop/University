#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>

int serve_client(int client_fd){
        uint32_t nr;
        int res = read(client_fd, &nr, sizeof(uint32_t));
        if(res == -1){
                perror("Read error!\n");
                close(client_fd);
                return -1;
        }
        nr = ntohl(nr);
        char buffer[nr + 1];
        res = read(client_fd, buffer, nr + 1);
        if(res == -1){
                perror("Read error!\n");
                close(client_fd);
                return -1;
        }
        printf("Client said: %s.\n", buffer);
        return 0;
}

int main(){
        uint16_t port = 1234;
        int backlog = 7;
        char address[256] = "192.168.50.14";
        int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if(sock_fd == -1){
                perror("Socket error!\n");
                return -1;
        }
        printf("Socket successfully created.\n");

        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
		server_addr.sin_addr.s_addr = INADDR_ANY;
        // inet_aton(address, &server_addr.sin_addr);
        socklen_t server_addr_len = sizeof(server_addr);
        int res = bind(sock_fd, (const struct sockaddr *) &server_addr, server_addr_len);
        if(res == -1){
                perror("Bind error!\n");
                return -1;
        }
        printf("Successfully bound to address %s and port %d.\n", address, port);
        res = listen(sock_fd, backlog);

		if(res == -1){
                perror("Listen error!\n");
                return -1;
        }
        printf("Listen successfully created with %d places.\n", backlog);
        struct sockaddr_in client_addr;
        socklen_t client_addr_len;
        while(1){
                int client_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_addr_len);
                if(client_fd == -1){
                        perror("Accept error!\n");
                        continue;
                }
                printf("Client with ip %s and port %d has connected.\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                serve_client(client_fd);
        }
        return 0;
}
