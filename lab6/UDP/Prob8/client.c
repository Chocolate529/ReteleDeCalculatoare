#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
 
int main() {
  int c;
  struct sockaddr_in server;
  socklen_t l = sizeof(server);
  
  c = socket(AF_INET, SOCK_DGRAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, l);
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  uint16_t a,b;
  printf("Introduceti primul numar: ");
  scanf("%hd",&a);
  printf("Introduceti al doilea numar: ");
  scanf("%hd",&b);

  a = htons(a);
  b = htons(b);

  sendto(c, &a, sizeof(a), 0, (struct sockaddr *) &server, l);
  sendto(c, &b, sizeof(b), 0, (struct sockaddr *) &server, l);
  printf("numere trimise astept..\n");
  uint32_t cmmmc;
  uint16_t cmmdc;

  recvfrom(c, &cmmmc, sizeof(cmmmc), 0, (struct sockaddr *) &server, &l); 
  recvfrom(c, &cmmdc, sizeof(cmmdc), 0, (struct sockaddr *) &server, &l);
  
  cmmmc = ntohl(cmmmc);
  cmmdc = ntohs(cmmdc);

  printf("Cel mai mare divizor comun: %hd\n",cmmdc);
  printf("Cel mai mare multiplu comun: %d\n",cmmmc);
  close(c);
}
