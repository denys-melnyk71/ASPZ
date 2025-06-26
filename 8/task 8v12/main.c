#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define FILENAME "test_io.txt"
#define WRITE_DELAY 1   // секунди між записами
#define READ_DELAY 2    // секунди між читаннями
#define NUM_WRITES 5    // кількість записів
#define BUFFER_SIZE 64

int main() {
    pid_t pid;
    int fd;

    // Створюємо (чи очищуємо) файл
    fd = open(FILENAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open (init)");
        return 1;
    }
    close(fd);

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Дочірній процес: Пише в файл порціями
        fd = open(FILENAME, O_WRONLY | O_APPEND);
        if (fd == -1) {
            perror("open (child)");
            exit(1);
        }

        for (int i = 1; i <= NUM_WRITES; ++i) {
            char buffer[BUFFER_SIZE];
            snprintf(buffer, sizeof(buffer), "Рядок %d: Це запис з дочірнього процесу. \n", i);
            write(fd, buffer, strlen(buffer));
            printf("[Дочірній] Записано: %s", buffer);
            sleep(WRITE_DELAY);
        }

        close(fd);
        exit(0);
    } else {
        // 👨‍🦳 Батьківський процес: Читає частинами
        sleep(1);  // даємо дитині шанс щось записати

        fd = open(FILENAME, O_RDONLY);
        if (fd == -1) {
            perror("open (parent)");
            return 1;
        }

        char buffer[BUFFER_SIZE];
        ssize_t bytes;

        while (1) {
            lseek(fd, 0, SEEK_SET);  // читаємо з початку
            printf("[Батьківський] Поточний вміст файлу:\n");

            while ((bytes = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
                buffer[bytes] = '\0';
                printf("%s", buffer);
            }

            printf("-----\n");
            sleep(READ_DELAY);

            // Перевіряємо чи дочірній процес завершився
            int status;
            pid_t result = waitpid(pid, &status, WNOHANG);
            if (result == pid) {
                printf("[Батьківський] Дочірній процес завершився\n");
                break;
            }
        }

        close(fd);
    }

    return 0;
}
