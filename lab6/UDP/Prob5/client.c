#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
 
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
  
  uint8_t a;
  printf("Introduceti un nr intre 0 si 255: ");
  scanf("%hhu",&a);

  sendto(c, &a, sizeof(a), 0, (struct sockaddr *) &server, l);

  uint16_t suma_div;
  recvfrom(c, &suma_div, sizeof(suma_div), 0, (struct sockaddr *) &server, &l);

  suma_div = ntohs(suma_div);

  printf("Suma div: %hu\n", suma_div);

  close(c);
}
