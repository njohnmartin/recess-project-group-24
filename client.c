#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 2056

void read_from_server(int sockfd, char *response) {
    int bytes_read = 0;
    bzero(response, 1024);

    while(1) {
        int n = recv(sockfd, response + bytes_read, 1023, 0);

        if (n == -1) {
            perror("Cannot read from the server");
            exit(1);
        }
        else if (n > 0) {
            bytes_read += n;
            if (response[bytes_read - 1] == '\n') break;
        }
    }
    response[bytes_read] = '\0';
}

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    struct hostent *server;
    char msg_buffer[1024];
    char senderid[1024];
    char resp_buffer[1024];

    // create the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *) &server_addr, sizeof(server_addr));

    // setup server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);


    // Connect to the server
    printf("Connecting to String Task Server...\n");
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("ERROR: Unable to connect to server");
        exit(1);
    }
    printf("Connected\n");
    
    printf("\n\nENTER YOUR ID: ");
       
    fgets(senderid, 1023, stdin);
    int len = strlen(senderid);
    if (senderid[len - 1] == '\n') 
        senderid[--len] = '\0';
    send(sockfd, senderid, len, 0);
    
    while(1){

        printf("\n\nEnter command: ");
        bzero(msg_buffer, 1024);
        fgets(msg_buffer, 1023, stdin);
        int len = strlen(msg_buffer);
        if (msg_buffer[len - 1] == '\n') 
            msg_buffer[--len] = '\0';
        int n = send(sockfd, msg_buffer, len, 0);


        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }

        if (!strncmp(msg_buffer, "exit", 4))
            break;

        while (1) {
            read_from_server(sockfd, resp_buffer);

            if (strncmp(resp_buffer, "done", 4) == 0)
                break;
            printf("%s", resp_buffer);
        }

    }
        

    close(sockfd);


}
