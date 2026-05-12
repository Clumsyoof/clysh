#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define SH_R_BUFFSIZE 1024;
char* shell_read(void)
{
    int buffersize = SH_R_BUFFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char)*buffersize);
    int c;
    if(!buffer) {
        fprintf(stderr,"clysh: allocation error\n");
        exit(EXIT_FAILURE);
    }
    while(1) {
        c = getchar();
        if(c == EOF ||c == '\n') {
            buffer[position] = '\n';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;
        if(position>= buffersize) {
            buffersize += SH_R_BUFFSIZE;
            buffer = realloc(buffer,buffersize*sizeof(char));
            if(!buffer) {
                fprintf(stderr,"clysh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

#define SH_SPLIT_BUFFSIZE 64;
#define SH_DELIM "\t\r\n\a"
char** shell_split(char *line)
{
    int buffersize = SH_SPLIT_BUFFSIZE;
    int position = 0;
    char **buffer = malloc(sizeof(char*)*buffersize);
    char *token;
    if(!buffer) {
        fprintf(stderr,"clysh: allocation error\n");
        exit(EXIT_FAILURE);
    }
    token = strtok(line,SH_DELIM);
    while(token!=NULL) {
        buffer[position]=token;
        position++;
        if(position >= buffersize) {
            buffersize += SH_R_BUFFSIZE;
            buffer = realloc(buffer,buffersize*sizeof(char*));
            if(!buffer) {
                fprintf(stderr,"clysh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL,SH_DELIM);
    }
    buffer[position] = NULL;
    return buffer;
}
int shell_launch(char **args)
{
    pid_t pid, wpid;
    int status;
    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
        perror("clysh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("clysh");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}
