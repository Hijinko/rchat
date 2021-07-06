#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    if (argc < 3){
        printf("Invalid usage\n");
        exit(EXIT_FAILURE);
    }

    enum {MAX_BUFF = 256};

    char * p_server_address = argv[1];
    int port = atoi(argv[2]);

    // create server addr
    struct sockaddr_in server_addr_t;
    socklen_t server_len = sizeof(server_addr_t);
    memset(&server_addr_t, 0, server_len);
    server_addr_t.sin_family = AF_INET;
    server_addr_t.sin_port = htons(port);
    inet_aton(p_server_address, &server_addr_t.sin_addr);

    // create socket
    int h_server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (h_server_sock < 0){
        perror("error creating socket ");
        exit(EXIT_FAILURE);
    }

    // connect to socket
    if (connect(h_server_sock, (struct sockaddr *)&server_addr_t, server_len) < 0){
        perror("error connecting to socket ");
        exit(EXIT_FAILURE);
    }

    // send message
    char * p_client_message = "Hey!";
    if (send(h_server_sock, p_client_message, strlen(p_client_message), 0) < 0){
        perror("error sending message ");
        exit(EXIT_FAILURE);
    }
    printf("SEND >> %s\n", p_client_message);

    // receive message
    char server_message[MAX_BUFF] = {'\0'};
    if (recv(h_server_sock, server_message, MAX_BUFF - 1, 0) < 0){
        perror("error sending message ");
        exit(EXIT_FAILURE);
    }
    printf("RECV << %s\n", server_message);

    // close socket
    close(h_server_sock);
}
//end of file
