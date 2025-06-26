#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>

#define MAX_PATH 1024

int is_owner_and_executable(const struct stat *st) {
    return (st->st_uid == getuid()) && (st->st_mode & S_IXUSR) && S_ISREG(st->st_mode);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char cwd[MAX_PATH];
    char filepath[MAX_PATH];

    // Отримуємо поточний каталог
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        return 1;
    }

    dir = opendir(cwd);
    if (!dir) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        snprintf(filepath, sizeof(filepath), "%s/%s", cwd, entry->d_name);

        if (stat(filepath, &st) == -1)
            continue;

        if (is_owner_and_executable(&st)) {
            printf("Знайдено виконуваний файл: %s\n", entry->d_name);

            printf("Надати іншим користувачам дозвіл на читання? (y/n): ");
            char response;
            scanf(" %c", &response);

            if (response == 'y' || response == 'Y') {
                mode_t new_mode = st.st_mode | S_IROTH;
                if (chmod(filepath, new_mode) == -1) {
                    perror("chmod");
                } else {
                    printf("Дозвіл на читання для інших надано для %s\n\n", entry->d_name);
                }
            }
        }
    }

    closedir(dir);
    return 0;
}
