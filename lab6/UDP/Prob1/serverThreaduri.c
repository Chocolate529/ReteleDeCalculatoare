#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

struct client_request {
    struct sockaddr_in client;
    socklen_t l;
    uint16_t a, b;
    int s;
};

void *handle_client(void *arg) {
    struct client_request *req = (struct client_request *)arg;

    uint16_t a = ntohs(req->a);
    uint16_t b = ntohs(req->b);
    uint16_t suma = htons(a + b);

    sendto(req->s, &suma, sizeof(suma), 0,
           (struct sockaddr *)&req->client, req->l);

    free(req); // eliberăm memoria alocată pentru cerere
    return NULL;
}

int main() {
    int s;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("Eroare la creare socket server");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Eroare la bind");
        return 1;
    }

    printf("Server UDP pornit pe portul 1234...\n");

    while (1) {
        struct client_request *req = malloc(sizeof(struct client_request));
        if (!req) continue;

        req->l = sizeof(req->client);

        // primim primul număr
        if (recvfrom(s, &req->a, sizeof(req->a), MSG_WAITALL,
                     (struct sockaddr *)&req->client, &req->l) < 0) {
            perror("Eroare la recvfrom");
            free(req);
            continue;
        }

        // primim al doilea număr
        if (recvfrom(s, &req->b, sizeof(req->b), MSG_WAITALL,
                     (struct sockaddr *)&req->client, &req->l) < 0) {
            perror("Eroare la recvfrom");
            free(req);
            continue;
        }

        req->s = s;

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, req);
        pthread_detach(tid); // nu mai trebuie să așteptăm thread-ul
    }

    close(s);
    return 0;
}

