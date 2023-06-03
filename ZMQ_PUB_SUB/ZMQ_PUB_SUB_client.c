#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>

int main(int argc, char *argv[]) {
    // Socket to talk to server
    void* context = zmq_ctx_new();
    void* socket = zmq_socket(context, ZMQ_SUB);
    printf("Collecting updates from weather server...\n");
    zmq_connect(socket, "tcp://localhost:5556");

    // Subscribe to zipcode, default is NYC, 10001
    char* zip_filter = (argc > 1) ? argv[1] : "10001";
    zmq_setsockopt(socket, ZMQ_SUBSCRIBE, zip_filter, strlen(zip_filter));

    // Process 20 updates
    int total_temp = 0;
    for (int update_nbr = 0; update_nbr < 20; update_nbr++) {
        char string[50];
        zmq_recv(socket, string, 50, 0);
        int zipcode, temperature, relhumidity;
        sscanf(string, "%d %d %d", &zipcode, &temperature, &relhumidity);
        total_temp += temperature;
        // Added from the original code
        printf("Receive temperature for zipcode '%s' was %d F\n", zip_filter, temperature);
    }
    printf("Average temperature for zipcode '%s' was %d F\n", zip_filter, total_temp / 20);

    zmq_close(socket);
    zmq_ctx_destroy(context);
    return 0;
}