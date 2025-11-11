#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
 
#define MAX_SIZE 101

int main() {
  int c;
  struct sockaddr_in server;
  socklen_t l = sizeof(server);
  
  c = socket(AF_INET, SOCK_DGRAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0,l );
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  char s[MAX_SIZE];
  uint8_t start,end;

  printf("Introduceti un sir de caractere: ");
  if(fgets(s,MAX_SIZE,stdin)){
  	s[strcspn(s,"\n")] = '\0';
  }else {
  	printf("Eroare citire sir\n");
  	return 1;
  }
  printf("Introduceti index de start subsir: ");
  scanf("%hhd", &start);
  printf("Introduceti index de end subsir: ");
  scanf("%hhd", &end);

  sendto(c, s, MAX_SIZE, 0, (struct sockaddr *)&server, l);
  sendto(c, &start, 1, 0, (struct sockaddr *)&server, l);
  sendto(c, &end, 1, 0, (struct sockaddr *)&server, l);
 printf("trimis astept resp...\n");
  char resp[MAX_SIZE];
  recvfrom(c, resp, MAX_SIZE, 0, (struct sockaddr *)&server, &l);

  printf("Subsirul este: %s \n", resp);


 close(c);
}
