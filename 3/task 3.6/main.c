#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <signal.h>

void handler(int sig) {
    printf("Stack overflow detected (signal %d). Exiting.\n", sig);
    exit(1);
}

void recursive_function(int depth) {
    char buffer[1024]; // Використання стеку
    printf("Recursion depth: %d\n", depth);
    buffer[0] = depth; // щоб не оптимізувався
    recursive_function(depth + 1);
}

int main() {
    struct rlimit limit;
    limit.rlim_cur = 1024 * 32;  // 32 KB stack
    limit.rlim_max = 1024 * 32;  // max also 32 KB

    if (setrlimit(RLIMIT_STACK, &limit) != 0) {
        perror("setrlimit failed");
        return 1;
    }

    // Перехоплюємо segmentation fault
    signal(SIGSEGV, handler);

    printf("Starting recursive calls with limited stack (32 KB)...\n");
    recursive_function(1);

    return 0;
}
