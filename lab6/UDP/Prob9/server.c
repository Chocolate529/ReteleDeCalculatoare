#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <time.h> 
uint64_t htonll(uint64_t value) {
	#if __BYTE_ORDER == __LITTLE_ENDIAN
    		return ((uint64_t)htonl(value & 0xFFFFFFFFULL) << 32) | htonl(value >> 32);
	#else
    		return value;
	#endif
}


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
  	char req[4];

  	recvfrom(s, req, 4, 0, (struct sockaddr *) &client, &l);

  	time_t seconds = time(NULL);
 	
        
 	 

  	seconds = htonll(seconds);
	sendto(s, &seconds, sizeof(seconds),0, (struct sockaddr *) &client, l);
  } 
  close(s);
}
