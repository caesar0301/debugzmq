#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 4321
#define SERVER_IP "127.0.0.1"

int main() {
    struct sockaddr_in server_addr;

    for (int i = 0; i < 3; i++) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("Socket creation failed");
            continue;
        }

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);

        if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
            perror("Invalid address / Address not supported");
            close(sock);
            continue;
        }

        printf("Attempt %d: Connecting to server...\n", i + 1);
        if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0) {
            printf("Attempt %d: Connection successful\n", i + 1);
        } else {
            perror("Connection failed");
        }

        close(sock);
        sleep(1); // Pause 1 second between attempts
    }

    return 0;
}
