#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 101

int main() {
  
  struct sockaddr_in server, client;
  int s;
  
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
 
  socklen_t l = sizeof(client);
  memset(&client, 0, sizeof(client));
  while(1){
  char* sir = malloc(MAX_LEN);
  if(sir == NULL){
  	printf("Eroare la malloc\n");
	return 1;
  }

  recvfrom(s, sir, MAX_LEN, 0, (struct sockaddr *) &client, &l);
  printf("%s\n",sir);
  uint16_t nr_spatii=0;
  for(int i = 0; i < strlen(sir); i++){
  	if(sir[i] == ' '){
		nr_spatii++;
	}
  }

  nr_spatii = htons(nr_spatii);
  sendto(s, &nr_spatii, sizeof(nr_spatii), 0, (struct sockaddr *) &client, l);
  }
  close(s);
}
