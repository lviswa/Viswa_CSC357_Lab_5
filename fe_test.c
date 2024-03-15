#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h> 

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        return -1;
    }

    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        //char *args[] = {"odds", argv[1], NULL};
        //execl("./odds", args);
        //perror("execvp odds");
        //exit(EXIT_FAILURE);
        execl("./odds.c", "odds", argv[1], (char *)NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        execl("./evens", "evens", argv[1], (char *)NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }
    int status1, status2;
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    return 0;
}
