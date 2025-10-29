#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
int main() {
  int c;
  struct sockaddr_in server;
  
  
  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }
  
  char* sir = malloc(256);
  if(sir == NULL){
  	printf("Eroare la malloc");
	return 1;
  }

  fgets(sir,255,stdin);
  sir[strcspn(sir, "\n")] = 0;

  int len = strlen(sir);
  int net_len = htons(len);


  int index, lenght;
  printf("Introduceti index de strat: \n");
  scanf("%d",&index);

  printf("Introduceti lungime subsir: \n");
  scanf("%d", &lenght);

  send(c, &net_len, sizeof(net_len), 0);
  send(c, sir, len, 0);

  int net_index, net_lenght;
  
  net_index = htons(index);
  net_lenght = htons(lenght);

  send(c, &net_index, sizeof(net_index), 0);
  send(c, &net_lenght, sizeof(net_lenght), 0);

  int lenght_allowed;
  recv(c, &lenght_allowed, sizeof(lenght_allowed), 0);
  lenght_allowed = ntohs(lenght_allowed);
  printf("Lungime subsir: %d\n",lenght_allowed);
  char* subsir = malloc(lenght_allowed);
  if(subsir == NULL){
  	printf("eroare la malloc\n");
	return 1;
  }
  recv(c, subsir, lenght_allowed, 0);
  printf("Subsirul este:%s\n", subsir);

  free(subsir);
  free(sir); 
  close(c);
}
