#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <sys/param.h>
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
  	uint16_t a,b;

	printf("Astept numere..\n");
	  recvfrom(s, &a, sizeof(a), 0, (struct sockaddr *) &client, &l);
	  recvfrom(s, &b, sizeof(b), 0, (struct sockaddr *) &client, &l);

 	 a = ntohs(a);
 	 b = ntohs(b);
 	 printf("Numere primite: %hd, %hd\n", a, b);
	 uint32_t cmmmc;
 	 uint16_t cmmdc;

	 for(int i = MIN(a,b); i > 0; i--){
	 	if(a % i == 0 && b % i == 0){
			cmmdc = i;
			break;
		}
	 }

	cmmmc = (a*b)/cmmdc;

  	cmmmc = htonl(cmmmc);
       	cmmdc = htons(cmmdc);
	 sendto(s, &cmmmc, sizeof(cmmmc), 0, (struct sockaddr *) &client, l);
         sendto(s, &cmmdc, sizeof(cmmdc), 0, (struct sockaddr *) &client, l);

  
  }
  close(s);
}
