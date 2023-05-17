#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    void* context = zmq_ctx_new();
    void* socket = zmq_socket(context, ZMQ_REQ);
    zmq_connect(socket, "tcp://localhost:5555");

    printf("this is request-reply pattern\nyou will receive a message you entered.\nbut if you enter 'hello', the you will receive 'world'.\n");
 
    while(1) {
        char buffer[1024];
        memset(buffer, 0, 1024);
        printf("Enter message : ");
        fgets(buffer, 1024, stdin);
        zmq_send(socket, buffer, strlen(buffer), 0);
        if (strncmp(buffer, "exit", 4) == 0)
        {
            break;
        }
        //  Get the reply.
        zmq_recv(socket, buffer, strlen(buffer), 0);
        printf("Received reply : %s\n\n", buffer);
        memset(buffer, 0, 1024);

    }

    printf("exit program...");
    zmq_close(socket);
    zmq_ctx_destroy(context);
    return 0;
}