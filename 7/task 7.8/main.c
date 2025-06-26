#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int is_regular_file(const char *path) {
    struct stat st;
    if (stat(path, &st) != 0)
        return 0;
    return S_ISREG(st.st_mode);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    char filepath[1024];

    dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Пропускаємо "." та ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Перевіряємо, чи це звичайний файл
        if (!is_regular_file(entry->d_name))
            continue;

        // Запит на видалення
        printf("Видалити файл \"%s\"? (y/n): ", entry->d_name);
        char answer;
        scanf(" %c", &answer);

        if (answer == 'y' || answer == 'Y') {
            if (remove(entry->d_name) == 0) {
                printf("Файл \"%s\" видалено.\n", entry->d_name);
            } else {
                perror("Помилка при видаленні");
            }
        }
    }

    closedir(dir);
    return 0;
}
