#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
int main(){
	
	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0){
		printf("Eroare la creare socket server\n");
		return 1;
	}

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if ( bind(s, (struct sockaddr *) &server, sizeof(server)) < 0){
		printf("Eroare la bind\n");
		return 1;		
	} 

	listen(s, 5);

	struct sockaddr_in client;
	int l;
	l = sizeof(client);
	memset(&client, 0, sizeof(client));

	int c;
	while(1){
		int len;
		
		c = accept(s, (struct sockaddr *) &client, &l);
		printf("S-a conectat un client\n");

		recv(c, &len, sizeof(len), MSG_WAITALL);
		len = ntohs(len);
		printf("RECEIVED %d\n",len);
		char* sir = malloc(len);
		if(sir == NULL){
			printf("Eroare la malloc\n");
			return 1;
		}

		recv(c, sir, len, MSG_WAITALL);
		printf("RECEIVED\n");
		int nr_spatii = 0;
		for(int i = 0; i < len; i++){
			if(sir[i] == ' '){
				nr_spatii++;
			}
		}
		nr_spatii = htons(nr_spatii);
		send(c, &nr_spatii, sizeof(nr_spatii), 0);
		printf("SENT\n");
		close(c);
		
	}

	return 0;
}
