#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>
#include <time.h>

int main() {
    printf("Publishing updates at weather server...\n");
    
    void* context = zmq_ctx_new();
    void* socket = zmq_socket(context, ZMQ_PUB);
    zmq_bind(socket, "tcp://*:5556");
    
    while (1) {
        int zipcode = rand() % 100000 + 1;
        int temperature = rand() % 215 - 80;
        int relhumidity = rand() % 51 + 10;
        
        char update[50];
        sprintf(update, "%d %d %d", zipcode, temperature, relhumidity);
        zmq_send(socket, update, strlen(update), 0);
        
    }
    
    zmq_close(socket);
    zmq_ctx_destroy(context);
    return 0;
}