#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server;
    char buffer[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    printf("Connected to server.\n");

    while (1) {
        printf("Client: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        send(sock, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "exit") == 0)
            break;

        memset(buffer, 0, sizeof(buffer));
        recv(sock, buffer, sizeof(buffer) - 1, 0);

        printf("Server: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    close(sock);

    return 0;
}