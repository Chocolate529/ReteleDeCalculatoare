#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h> 
#define MAX_LEN 101

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
  
  socklen_t l = sizeof(server);

  char* sir = malloc(MAX_LEN);
  if(sir == NULL){
  	printf("Eroare la malloca\n");
 	return 1;
  }

  printf("Introdu sirul: ");
    if (fgets(sir, MAX_LEN, stdin) != NULL) {
        sir[strcspn(sir, "\n")] = '\0';
    } else {
        printf("Eroare la citire.\n");
    }
  printf("Sirul este %s\n",sir);
  sendto(c, sir, MAX_LEN, 0, (struct sockaddr *) &server, l);
  
  uint16_t nr_spatii = 0;
  recvfrom(c, &nr_spatii, sizeof(nr_spatii), 0, (struct sockaddr *) &server, &l);

  nr_spatii = ntohs(nr_spatii);

  printf("Numarul de spatii este: %hd \n", nr_spatii);

  close(c);
}
