#include "client.h"

int main(int argc, char *argv[]) {

    uint16_t port;
    uint32_t server_ip;

    if(argc < 3) {
        port = DEFAULT_SERVER_PORT;
        server_ip = atoi(DEFAULT_SERVER_IP);

    } else {
        port = atoi(argv[2]);
        server_ip = atoi(argv[1]);
    }

}