#include "cmd.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

typedef int (*Shell)(char **);

Shell builtin_func[]= {
  &shell_cd,
  &shell_help,
  &shell_exit
};

int num_builtins()
{
  return sizeof(builtin_str) / sizeof(char *);
}

int shell_cd(char **args) 
{
  
    if (args[1] == NULL) {
        fprintf(stderr, "clysh: expected argument to \"cd\"\n");
  
    } else {
        if (chdir(args[1]) != 0) {
           perror("clysh");
        }
    }
  
    return 1;
}

int shell_help(char **args)
{
  int i;
  
  printf("an experemental shell based on Stephen Brennan's LSH\n"
        "Type program names and arguments, and hit enter.\n"
        "The following are built in:\n");

  for (i = 0; i < num_builtins(); i++) {
   
      printf("  %s\n", builtin_str[i]);
  
  }
  
  printf("Use the man command for information on other programs.\n");
  
  return 1;
}

int shell_exit(char **args)
{
  return 0;
}

int shell_execute(char **args)
{
  int i;
  
  if (args[0] == NULL) {
       return 1;
  }
  
  for (i = 0; i < num_builtins(); i++) {
    
      if (strcmp(args[0], builtin_str[i]) == 0) {
      
        return (*builtin_func[i])(args);
    }
  }
  
  return shell_launch(args);
}
