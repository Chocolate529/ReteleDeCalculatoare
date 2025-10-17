#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#define LEN 256

int main(){
	
	int c = socket(AF_INET, SOCK_STREAM, 0);
	if(c < 0){
		printf("Eroare la creare socket client\n");
		return 1;
	}

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(c,(struct sockaddr *) &server, sizeof(server)) < 0){
		printf("Eroare conectare la server\n");
		return 1;
	}

	char* sir = malloc(LEN);
	if(sir == NULL){
		printf("Eroare la malloc\n");
		return 1;
	}	
	
	printf("Introduceti un sir de caracter: ");
	fgets(sir,LEN,stdin);
	printf("Sirul are %ld caractere \n", strlen(sir));

	int len = strlen(sir);
	len = ntohs(len);
	send(c, &len, sizeof(len), 0);
	printf("SENT\n");

	send(c, sir, len, 0);
	printf("SENT\n");
	int nr_spatii;
	recv(c, &nr_spatii, sizeof(int), 0);
	nr_spatii = htons(nr_spatii);
	printf("RECEIVED\n");
	printf("Numarul de spatii din sir este %d \n",nr_spatii);


	close(c);
	free(sir);
	return 0;
}
