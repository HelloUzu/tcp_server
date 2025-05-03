#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define CONNECT_PORT 8080

int main(void){

    printf("\033[1m ---------------------- \n");
    printf("|      TCP Socket      |\n");
    printf("|     Created by Uzu   |\n");
    printf(" ---------------------- \n\n");

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(server_fd == -1){
        printf("\033[31;1m[!] Impossible to create socket!\033[0m\n");
        exit(-1);
    }

    printf("\033[32;1m[!] Socket created with success.\033[0m\n");

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(CONNECT_PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        printf("\033[31;1m[!] Error on function bind.\033[0m\n");
        exit(-1);
    }

    if(listen(server_fd, 1) == -1){
        printf("\033[31;1m[!] Error on function listen.\033[0m\n");
        exit(-1);
    }

    printf("\033[32;1m[!] Listening at the PORT: %d...\033[0m\n", CONNECT_PORT);

    while(1){
        int addr_len = sizeof(address);
        int client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addr_len);

        if (client_fd == -1) {
            printf("\033[31;1m[!] Error on function accept.\033[0m\n");
            exit(-1);
        }

        printf("\033[32;1m[!] Client connected.\033[0m\n");

        char *welcome = "Welcome to my TCP/IP server.";
        send(client_fd, welcome, strlen(welcome), 0);

        close(client_fd);
    }    

    close(server_fd);

    return 0;
}
