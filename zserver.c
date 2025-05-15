#include <zmq.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    void *context = zmq_ctx_new();
    void *responder = zmq_socket(context, ZMQ_REP);
    int rc = zmq_bind(responder, "tcp://*:4321");
    if (rc != 0) {
        perror("Server bind failed");
        return 1;
    }

    printf("ZMQ Server is listening on port 4321...\n");

    while (1) {
        char buffer[64] = {0};
        zmq_recv(responder, buffer, sizeof(buffer) - 1, 0);
        printf("Received: %s\n", buffer);

        // Send reply
        const char *reply = "OK";
        zmq_send(responder, reply, strlen(reply), 0);
    }

    zmq_close(responder);
    zmq_ctx_destroy(context);
    return 0;
}
