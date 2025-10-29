#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
int getDivizori(int n, int* divs){
	int cnt = 0;
	int d = 1;
	printf("Numarul %d\n",n);
	while(d <= n){
		if(n % d == 0){
			divs[cnt++] = d;
			printf("%d\n",d);
		}
		d++;
	}
	return cnt;
}

int main() {
  int s;
  struct sockaddr_in server, client;
  int c, l;
  
  s = socket(AF_INET, SOCK_STREAM, 0);
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
 
  listen(s, 5);
  
  l = sizeof(client);
  memset(&client, 0, sizeof(client));
  
  while (1) {
    uint16_t a;
    c = accept(s, (struct sockaddr *) &client, &l);
    printf("S-a conectat un client.\n");
    // deservirea clientului
    recv(c, &a, sizeof(a), MSG_WAITALL);
    
    a = ntohs(a);
    
    int nrDivizori = 0;
    int* divizori = malloc(sizeof(int)*a);
    if (divizori == NULL){
    	printf("Eroare la malloc\n");
    }

    nrDivizori = getDivizori(a, divizori);
    printf("Finish\n");
    nrDivizori = htons(nrDivizori);
    send(c, &nrDivizori, sizeof(nrDivizori), 0);
    nrDivizori = ntohs(nrDivizori);
	printf("%d\n",nrDivizori);
    for(int i = 0; i < nrDivizori; i++){
    	printf("divizor[%d]: %d\n", i+1,divizori[i]);
    }
    send(c, divizori, sizeof(int)*nrDivizori, 0);


    close(c);
    // sfarsitul deservirii clientului;
  }
}
