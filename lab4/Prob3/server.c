#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main () {

	int s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s < 0){
		printf("Eroare creare socket server\n");
		return 1;
	}

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if( bind(s, (struct sockaddr *) &server, sizeof(server)) <0) {
		printf("Eroare la bind\n");
		return 1;
	}

	listen(s,5);

	struct sockaddr_in client;
	int l;
	l = sizeof(client);
	memset(&client, 0, l);

	int c;
	while(1){
		c = accept(s, (struct sockaddr *) &client, &l);
		printf("S-a conectat un client\n");

		int len;
		recv(c, &len, sizeof(len), MSG_WAITALL);
		len = ntohs(len);

		char* buffer = malloc(len);
		if(buffer == NULL){
			printf("Eroare la malloc\n");
			return 1;
		}

		recv(c, buffer, len, MSG_WAITALL);

		for(int i = 0; i < len/2; i++){
			char aux = buffer[i];
			buffer[i] = buffer[len-i-1];
			buffer[len-i-1] = aux;
		}

		send(c, buffer, len, 0);

		close(c);
		free(buffer);
		
	}

	return 0;
}
