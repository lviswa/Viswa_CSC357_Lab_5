#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/types.h>

void limit_fork(rlim_t max_procs)
{
    struct rlimit rl;
    if (getrlimit(RLIMIT_NPROC, &rl) != 0) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }
    // Uncomment the next lines to debug the current limit values
    // printf("Current max processes limit: %lu\n", (unsigned long)rl.rlim_cur);
    // printf("Max processes limit (hard limit): %lu\n", (unsigned long)rl.rlim_max);

    // Ensure we do not exceed the hard limit
    if (max_procs > rl.rlim_max) {
        fprintf(stderr, "Requested max_procs exceeds the hard limit. Adjusting to hard limit.\n");
        rl.rlim_cur = rl.rlim_max;
    } else {
        rl.rlim_cur = max_procs;
    }

    if (setrlimit(RLIMIT_NPROC, &rl) != 0) {
        perror("setrlimit");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "Please provide a positive integer for N.\n");
        exit(EXIT_FAILURE);
    }

    limit_fork(300); // Call this early to limit processes before doing anything else

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        for (int i = 1; i <= N; i++) {
            if (i % 2 != 0) {
                printf("%d\n", i);
            }
        }
        exit(EXIT_SUCCESS);
    } else { // Parent process
        int status;

        for (int i = 1; i <= N; i++) {
            if (i % 2 == 0) {
                printf("\t%d\n", i);
            }
        }
        wait(&status); // Wait for the child process to terminate
    }

    return EXIT_SUCCESS;
}
