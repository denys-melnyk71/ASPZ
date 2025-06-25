#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/resource.h>
#include <errno.h>

#define MAX_FILES 1024
#define FILE_TEMPLATE "testfiles/file_%d.txt"

int main() {
    struct rlimit limit;
    if (getrlimit(RLIMIT_NOFILE, &limit) != 0) {
        perror("getrlimit failed");
        return 1;
    }

    printf("Max open files: soft = %ld, hard = %ld\n", limit.rlim_cur, limit.rlim_max);

    int fds[MAX_FILES];
    int count = 0;
    char filename[256];

    for (int i = 0; i < MAX_FILES; ++i) {
        snprintf(filename, sizeof(filename), FILE_TEMPLATE, i);

        int fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("open failed");
            printf("Stopped at %d files.\n", count);
            break;
        }

        fds[count++] = fd;
        printf("Opened file: %s (fd=%d)\n", filename, fd);
    }

    // Close opened files
    for (int i = 0; i < count; ++i) {
        close(fds[i]);
    }

    printf("Done. Opened %d files successfully.\n", count);
    return 0;
}
