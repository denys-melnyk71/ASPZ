#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // Встановлюємо pipe для запису в неблокуючий режим
    int flags = fcntl(pipefd[1], F_GETFL, 0);
    fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK);

    // Дуже великий буфер
    char buffer[100000];
    memset(buffer, 'A', sizeof(buffer));

    ssize_t count = write(pipefd[1], buffer, sizeof(buffer));
    if (count == -1) {
        perror("write");
    } else {
        printf("Спроба записати %zu байт, записано %zd байт\n", sizeof(buffer), count);
    }

    return 0;
}
