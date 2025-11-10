#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdbool.h>
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
 
  socklen_t  l = sizeof(client);
  memset(&client, 0, sizeof(client));
  
  while(1){
	uint16_t a;
  	recvfrom(s, &a, sizeof(a) ,MSG_WAITALL ,(struct sockaddr *) &client, &l);

	a = ntohs(a);

	bool prim = true;
	for(int d = 2; d < a; d ++){
		if(a % d == 0){
			prim = false;
		}
	}

	if(a == 1){
	 prim = false;
	}

	prim = htons(prim);
	sendto(s, &prim , sizeof(prim),0, (struct sockaddr *) &client, l);


  }

  close(s);
}
