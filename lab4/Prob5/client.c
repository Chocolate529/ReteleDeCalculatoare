#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
int main() {
  int c;
  struct sockaddr_in server;
  uint16_t a;
  
  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }
  
  printf("a = ");
  scanf("%hu", &a);
  
  a = htons(a);
 
  send(c, &a, sizeof(a), 0);
  
  
  int nrDivizori = 0;
  recv(c, &nrDivizori, sizeof(nrDivizori), MSG_WAITALL);
  nrDivizori = ntohs(nrDivizori);
  
  int* divizori = malloc(sizeof(int)*nrDivizori);
  if(divizori == NULL){
  	printf("eroare la malloc\n");
	return 1;
  }

  recv(c, divizori, sizeof(int)*nrDivizori, MSG_WAITALL);

  for(int i = 0; i < nrDivizori; i++){
 	printf("Divizor[%d]: %d\n", i+1, divizori[i]);
  }

  close(c);
}
