#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char ** argv) {
    if (argc != 2) {
        printf("Usage : %s <string>\n", argv[0]);
    }
    printf("%s\n", argv[1]);
}