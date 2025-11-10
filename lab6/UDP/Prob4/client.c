#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

int main() {
  int c;
  struct sockaddr_in server;
  
  
  
  c = socket(AF_INET, SOCK_DGRAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  char* sir = malloc(MAX_SIZE);
  if(sir == NULL){
  	printf("Eroare la malloc\n");
	return 1;
  }

  fgets(sir,MAX_SIZE,stdin);
  sir[strcspn(sir,"\n")] = 0;

  sendto(c, sir, 100, 0, (struct sockaddr *) &server, sizeof(server));

  memset(sir,0,MAX_SIZE);
  recvfrom(c, sir, 100, 0, (struct sockaddr *) &server, sizeof(server));
  printf("%s\n",sir);
  free(sir);
  
  close(c);
}
