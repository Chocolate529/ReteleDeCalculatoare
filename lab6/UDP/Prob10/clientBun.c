#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdint.h>

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
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // sau IP-ul serverului

    char hostname[101];
    printf("Introduceti un nume de calculator: ");
    fgets(hostname, 101, stdin);
    hostname[strcspn(hostname, "\n")] = '\0';

    sendto(c, hostname, strlen(hostname), 0, (struct sockaddr*)&server, l);

    uint32_t ip_numeric;
    recvfrom(c, &ip_numeric, sizeof(ip_numeric), 0, (struct sockaddr*)&server, &l);

    if (ip_numeric == 0) {
        printf("Eroare: numele calculatorului nu a putut fi rezolvat.\n");
    } else {
        struct in_addr addr;
        addr.s_addr = ip_numeric;
        printf("Adresa IP a calculatorului %s este: %s\n", hostname, inet_ntoa(addr));
    }

    close(c);
    return 0;
}
