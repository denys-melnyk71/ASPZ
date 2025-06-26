#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Дочірній процес: виконує команду echo
        execlp("echo", "echo", "Hello from child", NULL);
        // Якщо exec не спрацював:
        perror("execlp failed");
        exit(1);
    } else {
        // Батьківський процес: чекає завершення дитини
        wait(NULL);
        printf("Parent: child has finished\n");
    }

    return 0;
}
