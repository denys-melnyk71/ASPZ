#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void list_files(const char *base_path) {
    struct dirent *dp;
    DIR *dir = opendir(base_path);

    if (!dir) {
        perror(base_path);
        return;
    }

    while ((dp = readdir(dir)) != NULL) {
        char path[1024];

        // Пропускаємо . і ..
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", base_path, dp->d_name);

        struct stat statbuf;
        if (stat(path, &statbuf) == -1) {
            perror("stat");
            continue;
        }

        if (S_ISDIR(statbuf.st_mode)) {
            printf("[DIR]  %s\n", path);
            // Рекурсивний виклик для підкаталогу
            list_files(path);
        } else {
            printf("       %s\n", path);
        }
    }

    closedir(dir);
}

int main() {
    const char *start_path = ".";  // поточна директорія
    list_files(start_path);
    return 0;
}
