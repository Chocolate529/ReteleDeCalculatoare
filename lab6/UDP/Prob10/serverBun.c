#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdint.h>

int main() {
    int s;
    struct sockaddr_in server, client;
    socklen_t l = sizeof(client);

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

    while (1) {
        char hostname[101];
        memset(hostname, 0, sizeof(hostname));
        int n = recvfrom(s, hostname, 100, 0, (struct sockaddr*)&client, &l);
        hostname[n] = '\0';

        printf("Am primit hostname: %s\n", hostname);

        struct hostent *host = gethostbyname(hostname);
        uint32_t ip_numeric = 0;  // 0 = eroare

        if (host != NULL && host->h_addrtype == AF_INET) {
            struct in_addr *addr = (struct in_addr *)host->h_addr_list[0];
            ip_numeric = addr->s_addr; // este deja în formă de rețea
            printf("Trimitem IP: %s\n", inet_ntoa(*addr));
        } else {
            printf("Hostname invalid sau nerecunoscut\n");
        }

        // trimitem oricum 4 octeți (0 dacă e eroare)
        sendto(s, &ip_numeric, sizeof(ip_numeric), 0, (struct sockaddr*)&client, l);
    }

    close(s);
    return 0;
}

