#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>


#define LOGFILE "/var/log/timer_daemon.log"
#define INTERVAL_SEC 10

void log_message(const char *message) {
    int fd = open(LOGFILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd >= 0) {
        dprintf(fd, "[%ld] %s\n", time(NULL), message);
        close(fd);
    }
}

void timer_handler(int sig, siginfo_t *si, void *uc) {
    (void)sig; (void)si; (void)uc;

    log_message("Launching external process...");

    pid_t pid = fork();
    if (pid == 0) {
        // child
        execl("/usr/bin/date", "date", NULL);
        exit(EXIT_FAILURE); // if execl fails
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        log_message("Process completed.");
    } else {
        log_message("Failed to fork process.");
    }
}

void daemonize() {
    pid_t pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS); // Parent exits

    setsid(); // Create new session
    umask(0); // Clear file permissions mask
    chdir("/");

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

int main() {
    daemonize();

    struct sigaction sa = {0};
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = timer_handler;
    sigaction(SIGRTMIN, &sa, NULL);

    timer_t timerid;
    struct sigevent sev = {0};
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;

    if (timer_create(CLOCK_REALTIME, &sev, &timerid) == -1) {
        log_message("Failed to create timer.");
        exit(EXIT_FAILURE);
    }

    struct itimerspec its;
    its.it_value.tv_sec = INTERVAL_SEC;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = INTERVAL_SEC;
    its.it_interval.tv_nsec = 0;

    if (timer_settime(timerid, 0, &its, NULL) == -1) {
        log_message("Failed to set timer.");
        exit(EXIT_FAILURE);
    }

    while (1) pause(); // Wait for signal
}
