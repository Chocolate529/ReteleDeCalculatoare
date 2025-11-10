#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>


int main() {
  int s;
  struct sockaddr_in server, client;
  int c, l;
  
  
  s = socket(AF_INET, SOCK_DGRAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socketului server\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  
  if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }
 
  l = sizeof(client);
  memset(&client, 0, sizeof(client));
 while(1){ 
  
  
  char* sir = malloc(100);
  if(sir == NULL){
  	printf("Eroare la malloc\n");
	return 1;
  }  
 
  recvfrom(s, sir, 100, MSG_WAITALL, (struct sockaddr *) &client, &l);
 if(fork() == 0){

  int c = socket(AF_INET, SOCK_DGRAM, 0);	 

  for(int i = 0; i < strlen(sir)/2; i++){
  	char aux = sir[i];
	sir[i] = sir[strlen(sir) - i-1];
	sir[strlen(sir)-i-1] = aux;
  }
  
  sendto(c, sir, 100, 0, (struct sockaddr *) &client, sizeof(client));  
  printf("sir trimis %s\n", sir);
  free(sir);
 }
 }
  close(s);
}
