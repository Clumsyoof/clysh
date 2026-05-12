#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "cmd.h"


void lsh_loop(void)
{
    char *line;
    char **args;
    int status;
    do {
        printf(">> ");
        line = shell_read();
        args = shell_split(line);
        status = shell_execute(args);

        free(line);
        free(args);

    }while(status);
}

int main(int argc,char** argv)
{
    lsh_loop();
    return EXIT_SUCCESS;
}
