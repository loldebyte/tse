#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

// Code revu issu initialement de https://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    char buffer[256];
    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }

    int portno = atoi(argv[2]);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    struct hostent *server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    ///////////////////////////////////////////////////////

    struct sockaddr_in serv_addr;
    bzero((char *)&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    // Conversion de l'ordre des bits pour le réseau et l'hote.
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }

    printf("Please enter the message: ");
    bzero(buffer, 256);

    ///////////////////////////////////////////////////////

    fgets(buffer, 255, stdin);

    ssize_t bytes_wrote = write(sockfd, buffer, strlen(buffer));
    if (bytes_wrote < 0) {
        error("ERROR writing to socket");
    }
    printf("Wrote %zd bytes\n", bytes_wrote);

    bzero(buffer, 256);

    ///////////////////////////////////////////////////////

    ssize_t bytes_read = read(sockfd, buffer, 255);
    printf("Read %zd bytes\n", bytes_read);

    if (bytes_read < 0) {
        error("ERROR reading from socket");
    }
    printf("%s\n", buffer);
    return 0;
}
