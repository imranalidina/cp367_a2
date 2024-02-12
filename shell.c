#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64

int main() {
    char cmd[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    int i = 0;
    pid_t pid;
    int status;

    while (1) {
        printf("myshell> ");
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            printf("\n");
            continue;
        }

        for (i = 0; i < MAX_ARGS; i++) {
            args[i] = strtok(i == 0 ? cmd : NULL, " \n");
            if (args[i] == NULL) {
                break;
            }
        }

        if (strcmp(args[0], "q") == 0 || strcmp(args[0], "Q") == 0) {
            break;
        }

        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            if (execvp(args[0], args) < 0) {
                perror("execvp");
                exit(1);
            }
        } else {
            wait(&status);
        }
    }

    return 0;
}
