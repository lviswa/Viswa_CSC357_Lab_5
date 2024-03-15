#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        return -1;
    }

    int N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "Please provide a positive integer for N.\n");
        return -1;
    }

    for (int i = 1; i <= N; i++) {
        if (i % 2 == 0) {
            printf("\t%d\n", i);
        }
    }

    return 0;
}
