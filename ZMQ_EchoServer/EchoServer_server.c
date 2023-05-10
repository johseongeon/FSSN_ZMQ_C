#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>

int main()
{
    void* context = zmq_ctx_new();          
    void* responder = zmq_socket(context, ZMQ_REP);
    zmq_bind(responder, "tcp://*:5555");

    while (1) {
        char buffer[1024];
        memset(buffer, 0, 1024);
        zmq_recv(responder, buffer, 1024, 0);  // receive a message from the client
        printf("Received: %s\n", buffer);
        if (strncmp(buffer, "exit", 4) == 0)
        {
            break;
        }
        zmq_send(responder, buffer, strlen(buffer), 0);  // send a message to the client
    }

    printf("exit...\n");
    zmq_close(responder);
    zmq_ctx_destroy(context);
    return 0;
}