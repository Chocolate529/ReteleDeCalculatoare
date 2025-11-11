#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
 
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
  	uint8_t a;
	recvfrom(s, &a, sizeof(a), 0, (struct sockaddr *) &client, &l);

	uint16_t suma_div = 0;
	for (int d = 1; d <= a; d++) {
   		 if (a % d == 0) {
       			 suma_div += d;
    		  }
	}

	suma_div = htons(suma_div);

	sendto(s, &suma_div, sizeof(suma_div), 0, (struct sockaddr *) &client, l);	
  
  }
  
  close(s);
}
