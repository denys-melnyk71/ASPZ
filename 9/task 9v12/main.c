#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int count = 0;

    while (1) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            printf("Створено процесів: %d\n", count);
            break;
        } else if (pid == 0) {
            // Дочірній процес одразу завершується
            exit(0);
        } else {
            count++;
        }
    }

    return 0;
}
