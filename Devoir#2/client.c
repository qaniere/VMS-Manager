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

    init_gui(); //Initialize GUI

    //Socket thread must go here

    gui_loop(); //Start GUI loop

    gui_cleanup();
    //Once the GUI loop is over, clean up the GUI
}
