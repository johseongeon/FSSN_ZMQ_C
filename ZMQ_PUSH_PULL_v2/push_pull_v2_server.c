#include <czmq.h>
#include <stdio.h>
#include <string.h>

int main() {
    zsock_t* publisher = zsock_new_pub("tcp://*:5557");
    zsock_t* collector = zsock_new_pull("tcp://*:5558");

    char* message;
    while (1) {
        zsock_recv(collector,"s", & message);
        printf("Server: publishing update => %s\n", message);
        zsock_send(publisher, "s", message);
    }
    return 0;
}