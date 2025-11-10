#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main(){

	int c;
	c = socket(AF_INET, SOCK_DGRAM, 0);
	if(c < 0){
		printf("Eroare la crearea socketului client\n");
		return 1;
	}

	struct sockaddr_in server;
	socklen_t l = sizeof(server);

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
        
	uint16_t a,b;
	printf("Primul numar: ");
	scanf("%hd", &a);
	printf("Al doilea numar: ");
	scanf("%hd", &b);

	a = htons(a);
	b = htons(b);
	sendto(c, &a, sizeof(a), 0, (struct sockaddr *) &server, sizeof(server));
	sendto(c, &b, sizeof(b), 0, (struct sockaddr *) &server, sizeof(server));

	uint16_t suma;
	recvfrom(c, &suma, sizeof(suma), MSG_WAITALL, (struct sockaddr *) &server, &l);
	
	suma = ntohs(suma);
	printf("Suma este %hd: ", suma);
close(c);
	return 0;
}
