#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int s;
    struct sockaddr_in server, client;

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("Eroare la crearea socketului server");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Eroare la bind");
        return 1;
    }

    socklen_t l = sizeof(client);
    memset(&client, 0, sizeof(client));

    while (1) {
        char hostname[101];
        int n = recvfrom(s, hostname, 100, 0, (struct sockaddr*)&client, &l);
        hostname[n] = '\0';

        printf("Am primit hostname: %s\n", hostname);

        struct hostent *host_entry;
        char ip[INET_ADDRSTRLEN];

        host_entry = gethostbyname(hostname);
        if (host_entry == NULL) {
            strcpy(ip, "Unknown");
        } else {
            inet_ntop(AF_INET, host_entry->h_addr_list[0], ip, sizeof(ip));
        }

        sendto(s, ip, strlen(ip), 0, (struct sockaddr*)&client, l);
        printf("Trimis IP: %s\n", ip);
    }

    close(s);
    return 0;
}

