#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

#define MAX_SIZE 101

int main() {
  int s;
  struct sockaddr_in server, client;
  
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
  char sir[MAX_SIZE];
  uint8_t start,end;

  recvfrom(s, sir, MAX_SIZE, 0, (struct sockaddr *)&client, &l);
  recvfrom(s, &start, 1, 0, (struct sockaddr *)&client, &l);
  recvfrom(s, &end, 1, 0, (struct sockaddr *)&client, &l);
  printf("primit\n"); 
  char resp[MAX_SIZE];

  if (end > strlen(sir)){
  	end = strlen(sir);
  }

  uint8_t len = end - start + 1;
  memcpy(resp,sir+start,len);
  printf("Subsirul este %s \n", resp);
  sendto(s, resp, len, 0, (struct sockaddr *)&client, l);
  }
  close(s);
}
