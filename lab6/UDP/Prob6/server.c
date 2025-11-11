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
	char ch;

	recvfrom(s, sir, MAX_SIZE, 0, (struct sockaddr *) &client, &l);
	recvfrom(s, &ch, 1, 0, (struct sockaddr *) &client, &l);

	ssize_t len = 0;
	int poz[MAX_SIZE];
  	for(int i = 0; i < strlen(sir); i++){
		if(sir[i] == ch){
			poz[len++] = i;
		}
	}

	sendto(s, poz, len*sizeof(int), 0, (struct sockaddr *) &client, l);
  }


  close(s);
}
