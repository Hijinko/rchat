#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

int main(void)
{
    enum {MAX_BUFF = 256};

    // create server addr
    struct sockaddr_in server_addr_t;
    socklen_t server_len = sizeof(server_addr_t);
    memset(&server_addr_t, 0, server_len);
    server_addr_t.sin_family = AF_INET;
    server_addr_t.sin_addr.s_addr = INADDR_ANY;
    server_addr_t.sin_port = htons(8080);

    // create socket
    int h_server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (h_server_sock < 0){
        perror("error creating socket ");
        exit(EXIT_FAILURE);
    }

    // bind socket
    if (bind(h_server_sock, (struct sockaddr *)&server_addr_t, server_len) < 0){
        perror("error binding socket ");
        exit(EXIT_FAILURE);
    }

    // listen on socket
    listen(h_server_sock, 5);

    // accept a client
    struct sockaddr_in client_addr_t;
    socklen_t client_len = sizeof(client_addr_t);
    memset(&client_addr_t, 0, client_len);
    int h_client_sock = accept(h_server_sock, (struct sockaddr *)&client_addr_t, &client_len);
    if (h_client_sock < 0){
        perror("error accepting connection ");
        exit(EXIT_FAILURE);
    }

    // receive for command
    char client_message[MAX_BUFF] = {'\0'}; 
    if (recv(h_client_sock, client_message, MAX_BUFF - 1, 0) < 0){
        perror("error receiving message ");
        exit(EXIT_FAILURE);
    }
    printf("RECV << %s\n", client_message);

    // respond to command
    char * p_server_message = "Hello World!";
    if (send(h_client_sock, p_server_message, strlen(p_server_message), 0) < 0){
        perror("error sending message ");
        exit(EXIT_FAILURE);
    }
    printf("SEND >> %s\n", p_server_message);

    // close socket
    close(h_server_sock);
}
// end of file
