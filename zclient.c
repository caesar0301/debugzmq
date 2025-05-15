#include <zmq.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    void *context = zmq_ctx_new();
    void *requester = zmq_socket(context, ZMQ_REQ);

    int rc = zmq_connect(requester, "tcp://127.0.0.1:4321");
    if (rc != 0) {
        perror("Client connect failed");
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        char message[64];
        snprintf(message, sizeof(message), "Ping %d", i + 1);

        printf("Sending: %s\n", message);
        zmq_send(requester, message, strlen(message), 0);

        char buffer[64] = {0};
        zmq_recv(requester, buffer, sizeof(buffer) - 1, 0);
        printf("Received reply: %s\n", buffer);

        sleep(1);
    }

    zmq_close(requester);
    zmq_ctx_destroy(context);
    return 0;
}
