#pragma once

int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_execute(char **args);

extern char *builtin_str[];
extern int (*builtin_func[]) (char **);
