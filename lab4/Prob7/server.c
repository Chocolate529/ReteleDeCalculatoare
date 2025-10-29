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
    recv(c, &len ,sizeof(len), MSG_WAITALL);
    len = ntohs(len);
    printf("Lungime sir: %d\n", len);
    char* sir = malloc(len);
    recv(c, sir, len, MSG_WAITALL);
	printf("Sir: %s\n",sir);
    int index,lenght;
    recv(c, &index, sizeof(index), MSG_WAITALL);
    recv(c, &lenght,sizeof(lenght), MSG_WAITALL);
    
    index = ntohs(index);
    lenght = ntohs(lenght);
	printf("index: %d lenght: %d\n",index,lenght);
    char* subsir = malloc(lenght+1);
    if(subsir == NULL){
    	printf("Eroare la malloc\n");
	return 1;
    }

    int stop_index = index+lenght;
    if(stop_index > len){
    	stop_index = len;
	lenght = stop_index - index;
    }
    printf("stop_index: %d\n",stop_index);
    strcpy(subsir,sir+index);
    memset(&subsir + stop_index, 0 , len-stop_index);
    subsir[lenght] = '\0';
    printf("subsir: %s\n", subsir);
    int net_lenght = htons(lenght);
    send(c, &net_lenght, sizeof(net_lenght), 0);
    send(c, subsir, lenght, 0);

    free(subsir);
    free(sir);
    close(c);
    // sfarsitul deservirii clientului;
  }
}
