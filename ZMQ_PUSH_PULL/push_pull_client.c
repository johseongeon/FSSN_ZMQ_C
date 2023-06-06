#include <czmq.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int main() {
    zsock_t* subscriber = zsock_new_sub("tcp://localhost:5557", "");
    assert(subscriber);
    zsock_t* publisher = zsock_new_push("tcp://localhost:5558");
    assert(publisher);
    
    srand((unsigned)time(NULL));
    while (1) {
    zmq_pollitem_t items[] = {
        { subscriber, 0, ZMQ_POLLIN, 0 }
    };
    int rc = zmq_poll(items, 1, 100);

    usleep(1000000);

    if (rc > 0 && items[0].revents & ZMQ_POLLIN) {
        int message;
        zsock_recv(subscriber,"i", & message);
        printf("I: received message %d\n", message);
    } else {
        int rand_num = rand() % 10 + 1;
        zsock_send(publisher,"i", rand_num);
        printf("I: sending message %d\n", rand_num);
        }
    }
    return 0;
}