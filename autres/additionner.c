#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char ** argv) {
    if (argc != 3) {
        printf("Usage : %s <int> <int>\n", argv[0]);
    }
    int nb1, nb2;
    nb1 = (int) strtol(argv[1], NULL, 10);
    nb2 = (int) strtol(argv[2], NULL, 10);
    printf("%d\n", nb1+nb2);
}