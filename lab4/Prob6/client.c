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
  
  char ch;
  printf("Introduceti un caracter\n");
  scanf("%c",&ch);
  getchar();
  char* sir = malloc(256);
  fgets(sir, 256, stdin);
  sir[strcspn(sir, "\n")] = 0;

  int len = strlen(sir);
  int net_len = htons(len);
  send(c, &net_len, sizeof(net_len), 0);
  send(c, sir, len, 0);
  send(c, &ch,  1, 0);

  int nrPozitii = 0;
  recv(c, &nrPozitii, sizeof(nrPozitii), 0);
  nrPozitii = ntohs(nrPozitii);

  int* pozitii = malloc(nrPozitii*sizeof(int));
  recv(c, pozitii, sizeof(int)*nrPozitii, 0);

  for(int i = 0; i < nrPozitii; i++){
  	printf("%c apare pe pozitia %d \n", ch, pozitii[i]);
  }
  
  free(sir);
  free(pozitii);
  close(c);
}
