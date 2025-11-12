#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int c;
    struct sockaddr_in server;
    socklen_t l = sizeof(server);

    c = socket(AF_INET, SOCK_DGRAM, 0);
    if (c < 0) {
        perror("Eroare la crearea socketului client");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    char hostname[101];
    printf("Introduceti un nume de calculator din retea: ");
    if (fgets(hostname, 101, stdin)) {
        hostname[strcspn(hostname, "\n")] = '\0';
    } else {
        printf("Eroare citire nume calculator\n");
        return 1;
    }

    sendto(c, hostname, strlen(hostname), 0, (struct sockaddr*)&server, l);

    char ip[INET_ADDRSTRLEN];
    int n = recvfrom(c, ip, sizeof(ip) - 1, 0, (struct sockaddr*)&server, &l);
    ip[n] = '\0';

    printf("IP-ul calculatorului %s este %s\n", hostname, ip);

    close(c);
    return 0;
}

