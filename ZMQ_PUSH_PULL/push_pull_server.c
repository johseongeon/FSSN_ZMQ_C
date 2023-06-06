#include <czmq.h>
#include <stdio.h>
#include <string.h>

int main() {
    zsock_t* publisher = zsock_new_pub("tcp://*:5557");
    zsock_t* collector = zsock_new_pull("tcp://*:5558");
    int message;
    while (1) {
        zsock_recv(collector,"i", & message);
        printf("I: publishing update %d\n", message);
        zsock_send(publisher, "i", message);
    }
    return 0;
}