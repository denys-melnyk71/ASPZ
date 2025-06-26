#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    const char *filename = "test.bin";
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    unsigned char buffer[4];

    // Створюємо файл і записуємо 10 байтів
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open (write)");
        return 1;
    }
    write(fd, data, sizeof(data));
    close(fd);

    // Відкриваємо файл для читання
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open (read)");
        return 1;
    }

    // Переміщаємо покажчик читання на 3-й байт
    if (lseek(fd, 3, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    // Зчитуємо 4 байти з позиції 3
    ssize_t bytesRead = read(fd, buffer, 4);
    if (bytesRead != 4) {
        perror("read");
        close(fd);
        return 1;
    }

    // Виводимо байти
    printf("Зчитані байти: ");
    for (int i = 0; i < 4; ++i) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    close(fd);
    return 0;
}
