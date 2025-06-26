#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void handler(int sig, siginfo_t *info, void *ctx) {
    printf("[Subscriber] Signal %d received from PID %d with value %d\n",
           sig, info->si_pid, info->si_value.sival_int);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <signal_offset>\n", argv[0]);
        exit(1);
    }

    int offset = atoi(argv[1]);
    int signo = SIGRTMIN + offset;

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(signo, &sa, NULL);

    printf("[Subscriber] Listening for signal %d (SIGRTMIN+%d). PID: %d\n", signo, offset, getpid());

    while (1) {
        pause();  // чекаємо на сигнал
    }

    return 0;
}
