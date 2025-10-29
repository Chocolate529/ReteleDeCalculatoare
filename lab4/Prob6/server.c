#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
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
 
    c = accept(s, (struct sockaddr *) &client, &l);
    printf("S-a conectat un client.\n");
    // deservirea clientului
    int len;
    recv(c, &len, sizeof(len), MSG_WAITALL);
    len = ntohs(len);

    char* sir = malloc(len);
    recv(c, sir, len, MSG_WAITALL);

    char ch;
    recv(c, &ch, 1, MSG_WAITALL);    

    int cnt = 0;
    int* pozitii = malloc(len);
    for(int i = 0; i < len; i++){
    	if(sir[i] == ch){
		
		pozitii[cnt++] = i;
	}
    }

   int net_cnt = htons(cnt);
    send(c, &net_cnt, sizeof(net_cnt), 0);
    send(c, pozitii, cnt*sizeof(int), 0);

    free(pozitii);
    free(sir);
    close(c);
    // sfarsitul deservirii clientului;
  }
}
