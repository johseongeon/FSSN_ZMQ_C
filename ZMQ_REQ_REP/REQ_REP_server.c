#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

//hello를 입력하면 world를, 이외의 메시지를 입력하면 메시지를 그대로 돌려주는 서버

int main(void)
{
    void* context = zmq_ctx_new();
    void* socket = zmq_socket(context, ZMQ_REP);
    zmq_bind(socket, "tcp://*:5555");

    while (1) {
        int B = 0;
        char buffer[1024];
        memset(buffer, 0, 1024);
        zmq_recv(socket, buffer, 1024, 0);
        
        sleep(1);

        if (strncmp(buffer, "hello", 5) == 0 && strlen(buffer) == 6) //입력받은 message가 'hello'면
        {
            zmq_send(socket, "world", 6, 0); //'world'를 send한다.
            B = 1;
        }

        printf("Received request: %s\n\n", buffer);


        if (strncmp(buffer, "exit", 4) == 0)
        {
            break;
        }

        if (B == 0)
        {
            zmq_send(socket, buffer, strlen(buffer), 0);
        }
    }

    printf("req-rep server is de-activated...\n\n");
    zmq_close(socket);
    zmq_ctx_destroy(context);
    return 0;
}