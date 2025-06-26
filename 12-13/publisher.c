#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <pid> <signal_offset> <value>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);
    int offset = atoi(argv[2]);
    int value = atoi(argv[3]);

    int signo = SIGRTMIN + offset;

    union sigval val;
    val.sival_int = value;

    if (sigqueue(pid, signo, val) == -1) {
        perror("sigqueue failed");
        return 1;
    }

    printf("[Publisher] Sent signal %d (SIGRTMIN+%d) with value %d to PID %d\n",
           signo, offset, value, pid);

    return 0;
}
