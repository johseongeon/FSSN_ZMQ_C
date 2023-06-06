#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <czmq.h>
#include <time.h>
#include <assert.h>

int main() {
    zsock_t* publisher = zsock_new_pub("tcp://*:5556");
    assert(publisher);
    printf("Publishing updates at weather server...\n");

    srand((unsigned int)time(NULL));

    char _zipcode[7];
    char _temperature[5];
    char _relhumidity[3];

    while (1) {
        int zipcode = rand() % 100000 + 1;
        int temperature = rand() % 215 - 80;
        int relhumidity = rand() % 51 + 10;
        
        sprintf(_zipcode, "%d", zipcode);
        sprintf(_temperature, "%d", temperature);
        sprintf(_relhumidity, "%d", relhumidity);
        zsock_send(publisher, "sss", _zipcode, _temperature, _relhumidity);
       
    }

    zsock_destroy(&publisher);

    return 0;
}