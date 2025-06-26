#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#define MAX_PATH 1024

void run_ls(const char *path) {
    printf("\n===== ls -l %s =====\n", path);
    char cmd[MAX_PATH];
    snprintf(cmd, sizeof(cmd), "ls -l %s", path);
    system(cmd);
}

void try_file_access(const char *filepath) {
    printf("Файл: %s\n", filepath);

    // Спроба читання
    int fd_read = open(filepath, O_RDONLY);
    if (fd_read >= 0) {
        printf("  * Читання дозволено\n");
        close(fd_read);
    } else {
        printf("  * Читання заборонено: %s\n", strerror(errno));
    }

    // Спроба запису
    int fd_write = open(filepath, O_WRONLY | O_APPEND);
    if (fd_write >= 0) {
        printf("  ! Запис дозволено (не виконується запис)\n");
        close(fd_write);
    } else {
        printf("  * Запис заборонено: %s\n", strerror(errno));
    }

    // Спроба виконання
    if (access(filepath, X_OK) == 0) {
        printf("  * Виконання дозволено\n");
    } else {
        printf("  * Виконання заборонено: %s\n", strerror(errno));
    }
}

void scan_directory(const char *dirpath, int max_files) {
    DIR *dir = opendir(dirpath);
    if (!dir) {
        perror("Не вдалося відкрити директорію");
        return;
    }

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL && count < max_files) {
        if (entry->d_type != DT_REG && entry->d_type != DT_LNK && entry->d_type != DT_UNKNOWN)
            continue; // Лише звичайні файли або символічні посилання

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char full_path[MAX_PATH];
        snprintf(full_path, sizeof(full_path), "%s/%s", dirpath, entry->d_name);

        try_file_access(full_path);
        count++;
    }

    closedir(dir);
}

int main() {
    const char *home_dir = getenv("HOME");
    if (!home_dir) {
        fprintf(stderr, "Не вдалося отримати домашній каталог.\n");
        return 1;
    }

    const char *dirs[] = { home_dir, "/usr/bin", "/etc" };

    for (int i = 0; i < 3; i++) {
        printf("\n\n=== Перевірка директорії: %s ===\n", dirs[i]);
        run_ls(dirs[i]);
        scan_directory(dirs[i], 5); // Перевірити перші 5 файлів
    }

    printf("\n[+] Готово.\n");
    return 0;
}
