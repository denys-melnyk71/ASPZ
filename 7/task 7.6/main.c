#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// Структура для зберігання імен каталогів
#define MAX_DIRS 1024

int is_directory(const char *name) {
    struct stat st;
    return stat(name, &st) == 0 && S_ISDIR(st.st_mode);
}

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    char *dirs[MAX_DIRS];
    int count = 0;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Пропускаємо . і ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (is_directory(entry->d_name)) {
            dirs[count] = strdup(entry->d_name);  // копіюємо ім’я
            count++;
            if (count >= MAX_DIRS) break;  // захист від переповнення
        }
    }

    closedir(dir);

    // Сортуємо імена каталогів
    qsort(dirs, count, sizeof(char *), compare);

    // Виводимо відсортовані імена
    printf("Список підкаталогів (алфавітно):\n");
    for (int i = 0; i < count; i++) {
        printf("%s/\n", dirs[i]);
        free(dirs[i]);  // звільняємо пам’ять
    }

    return 0;
}
