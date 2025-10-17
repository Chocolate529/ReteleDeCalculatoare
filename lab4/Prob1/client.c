#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>

int main(){
	

	
	int c;
	c = socket(AF_INET, SOCK_STREAM, 0);
	if(c < 0){
		printf("Eroare la crearea socketului client\n");
		return 1;
	}

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(c, (struct sockaddr *) &server, sizeof(server)) < 0){
		printf("Eroare la conectare la server\n");
		return 1;
	}


	int len;
	printf("Cate numere?:  \n");
	scanf("%d",&len);

	int* numbers;
	numbers = malloc(len*sizeof(int));
	if(numbers == NULL){
		printf("Eroare la malloc\n");
		return 1;
	}
	
	for(int i = 0; i < len; i++){
		printf("Numar %d: \n", i);
		scanf("%d",&numbers[i]);
		numbers[i] = htons(numbers[i]);
	}

	len = htons(len);
	send(c,&len, sizeof(len), 0);
	send(c,numbers, sizeof(int)*len, 0);
	
	int suma;
	recv(c, &suma, sizeof(suma), 0);
	suma = ntohs(suma);

	printf("Suma calculata de server este: %d\n",suma);

	free(numbers);
	close(c);

	return 0;
	
}
