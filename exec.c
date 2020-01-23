#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    char ** args = 0;
    args[0] = "additioner_noarg";
    execvp("additioner_noarg", args);
}