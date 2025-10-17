#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
int main(){
	
	int c = socket(AF_INET, SOCK_STREAM, 0);
	if(c < 0){
		printf("Eroare la crearea socketului client\n");
		return 1;
	}

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(c, (struct sockaddr *) &server, sizeof(server) )<0){
		printf("Eroare la conectare la server\n");
		return 1;
	}
	
	char* buffer = malloc(256);
	if(buffer == NULL){
		printf("Eroare la malloc\n");
		return 1;
	}
	printf("Introduceti un sir de caractere: ");
	fgets(buffer, 256, stdin);
	
	int len = strlen(buffer);
	len = ntohs(len);
	send(c, &len, sizeof(len), 0);

	send(c, buffer, len, 0);

	memset(buffer, 0, sizeof(buffer)); 
	
	recv(c, buffer, len, 0);
	printf("Sirul oglindit este: \n %s \n", buffer);
	close(c);
	free(buffer);
	
	return 0; 
}
