/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Code revu issu initialement de https://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html

void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    char buffer[256];

    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    ///////////////////////////////////////////////////////

    const int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    struct sockaddr_in serv_addr;
    bzero((char *)&serv_addr, sizeof(serv_addr));
    
    ///////////////////////////////////////////////////////

    int portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
            sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }
    listen(sockfd, 5);

    ///////////////////////////////////////////////////////

    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    const int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) {
        error("ERROR on accept");
    }
    bzero(buffer, 256);

    ///////////////////////////////////////////////////////

    const ssize_t bytes_read = read(newsockfd, buffer, 255);

    if (bytes_read < 0) {
        error("ERROR reading from socket");
    }
    printf("Read %zd bytes\n", bytes_read);
    printf("Here is the message: %s\n", buffer);

    ///////////////////////////////////////////////////////

    const ssize_t bytes_wrote = write(newsockfd, "I got your message", 18);
    if (bytes_wrote < 0) {
        error("ERROR writing to socket");
    }
    printf("Wrote %zd bytes\n", bytes_wrote);
    return EXIT_SUCCESS;
}
