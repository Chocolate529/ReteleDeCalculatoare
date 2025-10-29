#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_SIZE 1024

int main() {
    int c;
    struct sockaddr_in server;

    // Creare socket
    c = socket(AF_INET, SOCK_STREAM, 0);
    if (c < 0) {
        perror("Eroare creare socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(1234);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Conectare la server
    if (connect(c, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Eroare conectare la server");
        close(c);
        return 1;
    }

    char *sir1 = malloc(MAX_SIZE);
    char *sir2 = malloc(MAX_SIZE);
    if (!sir1 || !sir2) {
        perror("Eroare alocare memorie");
        close(c);
        return 1;
    }

    printf("Scrieti un sir de caractere:\n");
    fgets(sir1, MAX_SIZE, stdin);
    printf("Scrieti al doilea sir:\n");
    fgets(sir2, MAX_SIZE, stdin);

    // Eliminăm '\n' de la final (dacă există)
    sir1[strcspn(sir1, "\n")] = 0;
    sir2[strcspn(sir2, "\n")] = 0;

    int len1 = strlen(sir1);
    int len2 = strlen(sir2);

    printf("Lungimi: %d, %d\n", len1, len2);

    // Trimitem primul șir
    int net_len1 = htons(len1);
    send(c, &net_len1, sizeof(net_len1), 0);
    send(c, sir1, len1, 0);

    // Trimitem al doilea șir
    int net_len2 = htons(len2);
    send(c, &net_len2, sizeof(net_len2), 0);
    send(c, sir2, len2, 0);

    // Primim răspunsul
    char resp[MAX_SIZE];
    memset(resp, 0, MAX_SIZE);
    int bytes_received = recv(c, resp, MAX_SIZE - 1, 0);
    if (bytes_received < 0) {
        perror("Eroare la primirea datelor");
    } else {
        resp[bytes_received] = '\0';  // asigurăm terminator
        printf("Răspunsul de la server: %s\n", resp);
    }

    free(sir1);
    free(sir2);
    close(c);
    return 0;
}

