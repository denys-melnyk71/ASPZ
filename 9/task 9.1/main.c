#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

#define UID_THRESHOLD 1000  // для FreeBSD зазвичай 1000

int main() {
    FILE *fp;
    char line[1024];
    char *username, *uid_str;
    uid_t current_uid = getuid();

    struct passwd *pw = getpwuid(current_uid);
    if (!pw) {
        perror("getpwuid");
        return 1;
    }

    const char *current_user = pw->pw_name;

    fp = popen("getent passwd", "r");
    if (!fp) {
        perror("popen");
        return 1;
    }

    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        // Формат рядка: ім'я:х:UID:GID:коментар:домашній_каталог:шелл
        // strtok змінює буфер, тому копіюємо
        char line_copy[1024];
        strncpy(line_copy, line, sizeof(line_copy));
        line_copy[sizeof(line_copy) - 1] = '\0';

        username = strtok(line_copy, ":");
        strtok(NULL, ":"); // пропускаємо пароль
        uid_str = strtok(NULL, ":");

        if (!username || !uid_str)
            continue;

        int uid = atoi(uid_str);
        if (uid >= UID_THRESHOLD && strcmp(username, current_user) != 0) {
            printf("Інший звичайний користувач: %s (UID=%d)\n", username, uid);
            found = 1;
        }
    }

    pclose(fp);

    if (!found) {
        printf("Жодного іншого звичайного користувача не знайдено\n");
    }

    return 0;
}
