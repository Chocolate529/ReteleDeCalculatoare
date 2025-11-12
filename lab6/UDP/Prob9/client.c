#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>


uint64_t ntohll(uint64_t value) {
	#if __BYTE_ORDER == __LITTLE_ENDIAN
    		return ((uint64_t)ntohl(value & 0xFFFFFFFFULL) << 32) | ntohl(value >> 32);
	#else
   		return value;
	#endif
} 


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

  char req[4];
  strcpy(req, "GET");

  sendto(c, req, 4, 0, (struct sockaddr *) &server, l);

  time_t seconds;
  recvfrom(c, &seconds, sizeof(seconds),0, (struct sockaddr *) &server, &l);

  seconds = ntohll(seconds);

  printf("Numarul de secunde de la 1 ianuarie 1970 este: %ld\n", seconds);
  
  close(c);
}
