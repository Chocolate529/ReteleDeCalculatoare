#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 1000
int main() {
  int c;
  struct sockaddr_in server;
  uint16_t a, b, suma;
  
  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(2468);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("172.30.242.9");
  
  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }
  
  while(1){
       char* resp = malloc(MAX_SIZE);
       if(resp == NULL){
       	printf("Eroare la malloc\n");
	return 1;
       }
       recv(c, resp, 1000, 0);

	printf("Raspuns server: %s", resp);
	char* client_resp = malloc(MAX_SIZE);
        if(client_resp == NULL){
		printf("Eroare la malloc\n");
		return 1;
	}
	fgets(client_resp, MAX_SIZE, stdin);
	
	int len = strlen(client_resp);
	client_resp[len+1] = '\0';
	
	send(c, client_resp, len, 0);

       free(resp); 
       free(client_resp);
  }
  close(c);
}
