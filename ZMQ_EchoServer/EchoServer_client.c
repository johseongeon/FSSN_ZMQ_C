#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>

int main()
{
    void* context = zmq_ctx_new();       
    void* requester = zmq_socket(context, ZMQ_REQ);  
    zmq_connect(requester, "tcp://localhost:5555");   

    while (1) {
        char buffer[1024];
        memset(buffer, 0, 1024);
        printf("Enter message: ");
        fgets(buffer, 1024, stdin);
        if (strncmp(buffer, "exit", 4) == 0)
        {       
            zmq_send(requester, buffer, strlen(buffer), 0);
            break;
        }

        zmq_send(requester, buffer, strlen(buffer), 0);   // send a message to the server
        zmq_recv(requester, buffer, 1024, 0);              // receive a message frome the server

        printf("Received: %s\n", buffer);
    }

    zmq_close(requester);   
    zmq_ctx_destroy(context);  
    return 0;
}