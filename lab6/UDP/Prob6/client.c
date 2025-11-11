#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

#define MAX_SIZE 101

int main() {
  int c;
  struct sockaddr_in server;
  socklen_t l = sizeof(server);
  
  c = socket(AF_INET, SOCK_DGRAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, l);
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  char sir[MAX_SIZE];
  printf("Introduceti un sir de caractere: ");
  if(fgets(sir, MAX_SIZE, stdin)){
  	sir[strcspn(sir,"\n")] = '\0';
  } else {
  	printf("Eroare citire sir\n");
  }


  char ch;
  printf("Introduceti un caracter: ");
  scanf("%c", &ch);

  sendto(c, sir, strlen(sir)+1, 0, (struct sockaddr *) &server, l);
  sendto(c, &ch, 1, 0, (struct sockaddr *) &server, l);

  int poz[MAX_SIZE];
  ssize_t len = recvfrom(c, poz, MAX_SIZE*sizeof(int), 0, (struct sockaddr *) &server,&l);

  for(int i = 0; i < len/sizeof(int); i++){
  	printf("Caracterul apare pe pozitia: %d\n", poz[i]);
  
  } 
  
  close(c);
}
