#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <czmq.h>

int main(int argc, char** argv) {
    char* zip_filter = (argc > 1) ? argv[1] : "10001";
    zsock_t* subscriber = zsock_new_sub("tcp://localhost:5556", zip_filter);
    assert(subscriber);
    printf("Collecting updates from weather server...\n");

    char* _zipcode;
    char* _temperature;
    char* _relhumidity;
    int total_temp = 0;
    for (int update_nbr = 0; update_nbr < 20; update_nbr++) {
        zsock_recv(subscriber, "sss", &_zipcode, &_temperature, &_relhumidity);
        total_temp += atoi(_temperature);
        printf("Receive temperature for zipcode '%s' was %d F\n", zip_filter, atoi(_temperature));
        free(_zipcode);
        free(_temperature);
        free(_relhumidity);
    }
    printf("Average temperature for zipcode '%s' was %d F\n", zip_filter, total_temp / 20);

    zsock_destroy(&subscriber);

    return 0;
}