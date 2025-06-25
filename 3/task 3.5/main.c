#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Program need two arguments\n");
        return 1;
    }

    const char *src = argv[1];
    const char *dest = argv[2];

    int in = open(src, O_RDONLY);
    if (in < 0) {
        fprintf(stderr, "Cannot open file %s for reading\n", src);
        return 1;
    }

    int out = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out < 0) {
        close(in);
        fprintf(stderr, "Cannot open file %s for writing\n", dest);
        return 1;
    }

    // Буфер і ліміт розміру файлу
    char buf[BUFSIZE];
    ssize_t bytesRead, bytesWritten;

    struct rlimit lim;
    if (getrlimit(RLIMIT_FSIZE, &lim) == -1) {
        perror("getrlimit failed");
    }

    size_t totalWritten = 0;

    while ((bytesRead = read(in, buf, sizeof(buf))) > 0) {
        // Перевірка: чи не перевищимо ліміт
        if (lim.rlim_cur != RLIM_INFINITY && totalWritten + bytesRead > lim.rlim_cur) {
            fprintf(stderr, "File size limit exceeded. Copy aborted.\n");
            break;
        }

        bytesWritten = write(out, buf, bytesRead);
        if (bytesWritten < 0) {
            if (errno == EFBIG) {
                fprintf(stderr, "File size limit exceeded. Write failed.\n");
            } else {
                perror("Write failed");
            }
            break;
        }

        totalWritten += bytesWritten;
    }

    if (bytesRead < 0) {
        perror("Read failed");
    }

    close(in);
    close(out);
    return 0;
}
