#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char ** argv) {
    int pipefd[2];
    pid_t cpid;

    if (argc < 3) {
        printf("Usage : %s <prog1> <prog2> <prog2's_optional_arguments>\n", argv[0]);   // redirects prog2 <args> to prog1
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1) {
        perror("pipe");
       exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {
        close(pipefd[0]);   // child wont read
        printf("Child doing stuff\n");

        dup2(pipefd[1], STDOUT_FILENO);    // redirect STDOUT to the pipe
        dup2(pipefd[1], STDERR_FILENO);    // redirect STDERR to the pipe
        close(pipefd[1]);           // close the pipe so it is NULL terminated

        char * prog_to_exec = argv[2];  // argv[2] is the prog we want to exec
        char ** arguments = argv+2;
        printf("Hasta la vista, cruel world\n");
        execvp(prog_to_exec, arguments);
    }
    else {
        printf("waiting for ma boy\n");
        wait(NULL);
        printf("Not waiting anymore !\n");
        char ** args2 = argv;
        dup2(pipefd[0], STDIN_FILENO);
        read(pipefd[0], args2, 1024*sizeof(char)); // sizeofargs should be passed through the pipe, i s'pose
        execvp(argv[1], args2);
    }      
}
