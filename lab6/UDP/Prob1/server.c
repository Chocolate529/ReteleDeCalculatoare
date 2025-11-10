#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main() {
	int s;
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if(s < 0){
		printf("Eroare la creare socket server\n");
		return 1;
	}

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if( bind(s, (struct sockaddr *) &server, sizeof(server)) < 0){
		printf("Eroare la bind\n");
		return 1;
	}

	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));
	socklen_t l = sizeof(client);

	while(1){
	uint16_t a,b;
	recvfrom(s, &a, sizeof(a), MSG_WAITALL, (struct sockaddr *) &client, &l);
	recvfrom(s, &b ,sizeof(b), MSG_WAITALL, (struct sockaddr *) &client, &l);

	a = ntohs(a);
	b = ntohs(b);

	uint16_t suma = a + b;
	suma = htons(suma);
	sendto(s, &suma, sizeof(suma), 0, (struct sockaddr *) &client, l);
}
close(s);
	return 0;
}
