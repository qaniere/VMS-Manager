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

    int socket_fd = connect_to_server(server_ip, port);
    int client_id = get_client_id(socket_fd);

    init_gui(); //Initialize GUI

    update_client_id(client_id); 
    update_server_ip(server_ip);

    gui_loop(); //Start GUI loop

    gui_cleanup();
    //Once the GUI loop is over, clean up the GUI
}
