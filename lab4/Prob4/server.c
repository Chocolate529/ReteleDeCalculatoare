#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 1234

void sortare(char *s) {
    int n = strlen(s);
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (s[i] > s[j]) {
                char temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
}

void combine(char *dest, const char *a, const char *b) {
    int i = 0, j = 0, k = 0;
    while (a[i] != '\0' && b[j] != '\0') {
        if (a[i] < b[j]) dest[k++] = a[i++];
        else dest[k++] = b[j++];
    }
    while (a[i] != '\0') dest[k++] = a[i++];
    while (b[j] != '\0') dest[k++] = b[j++];
    dest[k] = '\0';
}

int main() {
    int s, c;
    struct sockaddr_in server, client;
    socklen_t l = sizeof(client);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("Eroare la socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Eroare la bind");
        close(s);
        return 1;
    }

    listen(s, 5);
    printf("Server pornit pe portul %d...\n", PORT);

    while (1) {
        c = accept(s, (struct sockaddr *)&client, &l);
        if (c < 0) {
            perror("Eroare la accept");
            continue;
        }

        printf("S-a conectat un client.\n");

        int len1, len2;
        recv(c, &len1, sizeof(len1), MSG_WAITALL);
        len1 = ntohs(len1);

        char *sir1 = malloc(len1 + 1);
        recv(c, sir1, len1, MSG_WAITALL);
        sir1[len1] = '\0';

        recv(c, &len2, sizeof(len2), MSG_WAITALL);
        len2 = ntohs(len2);

        char *sir2 = malloc(len2 + 1);
        recv(c, sir2, len2, MSG_WAITALL);
        sir2[len2] = '\0';

        printf("Am primit:\n1: %s\n2: %s\n", sir1, sir2);

        sortare(sir1);
        sortare(sir2);

        printf("Sortate:\n1: %s\n2: %s\n", sir1, sir2);

        char *interclasare = malloc(len1 + len2 + 1);
        combine(interclasare, sir1, sir2);

        printf("Interclasare: %s\n", interclasare);

        send(c, interclasare, strlen(interclasare), 0);

        free(sir1);
        free(sir2);
        free(interclasare);
        close(c);

        printf("Client deconectat.\n");
    }

    close(s);
    return 0;
}

