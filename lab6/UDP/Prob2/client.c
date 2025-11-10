#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdbool.h>
int main() {
  int c;
  struct sockaddr_in server;
  uint16_t a;
  
  
  
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

  printf("Scrieti un numar: ");
  scanf("%hd",&a);

  a = htons(a);
  sendto(c, &a ,sizeof(a),0, (struct sockaddr *) &server, sizeof(server));

  bool prim = false;
  recvfrom(c, &prim ,sizeof(prim),MSG_WAITALL, (struct sockaddr *) &server, &l);

  prim = ntohs(prim);
  if(prim){
  	printf("Numarul e prim\n");
  } else {
  	printf("Numarul nu e prim\n");
  }

  close(c);
}
