#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pwd.h>
#include <errno.h>

#define TMP_FILE "/tmp/tempfile_permission_test.txt"
#define USERNAME "denys" 

void error_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void drop_privileges(uid_t uid, gid_t gid) {
    if (setegid(gid) != 0 || seteuid(uid) != 0)
        error_exit("drop_privileges");
}

void restore_privileges() {
    if (seteuid(0) != 0 || setegid(0) != 0)
        error_exit("restore_privileges");
}

void create_temp_file_as_user(uid_t uid, gid_t gid) {
    drop_privileges(uid, gid);

    printf("[User] Створюємо тимчасовий файл: %s\n", TMP_FILE);
    FILE *f = fopen(TMP_FILE, "w");
    if (!f) error_exit("fopen");

    fprintf(f, "Це тестовий файл, створений користувачем.\n");
    fclose(f);
    printf("[User] Файл створено.\n");

    restore_privileges();
}

void change_ownership_and_permissions(const char *username) {
    printf("[Root] Змінюємо власника та права доступу за допомогою shell-команд\n");

    char cmd[256];

    // Зміна власника
    snprintf(cmd, sizeof(cmd), "chown %s %s", username, TMP_FILE);
    if (system(cmd) != 0) {
        fprintf(stderr, "Помилка під час виконання: %s\n", cmd);
        exit(EXIT_FAILURE);
    }

    // Зміна прав доступу
    snprintf(cmd, sizeof(cmd), "chmod 600 %s", TMP_FILE);
    if (system(cmd) != 0) {
        fprintf(stderr, "Помилка під час виконання: %s\n", cmd);
        exit(EXIT_FAILURE);
    }

    printf("[Root] Власник і права доступу змінені успішно\n");
}

void test_access_as_user(uid_t uid, gid_t gid) {
    drop_privileges(uid, gid);

    printf("[User] Перевіряємо доступ до файлу: %s\n", TMP_FILE);

    FILE *f = fopen(TMP_FILE, "r+");
    if (!f) {
        perror("[User] Не вдалося відкрити файл для читання/запису");
    } else {
        printf("[User] Файл відкрито для читання та запису.\n");
        fprintf(f, "Додано новий рядок від імені користувача.\n");
        fclose(f);
    }

    restore_privileges();
}

void cleanup() {
    printf("[Root] Видаляємо тимчасовий файл\n");
    if (remove(TMP_FILE) != 0) {
        perror("remove");
    }
}

int main() {
    if (geteuid() != 0) {
        fprintf(stderr, "⚠️ Цю програму потрібно запускати з правами root.\n");
        return 1;
    }

    struct passwd *pw = getpwnam(USERNAME);
    if (!pw) error_exit("getpwnam");

    uid_t user_uid = pw->pw_uid;
    gid_t user_gid = pw->pw_gid;

    printf("=== Етап 1: Створення файлу користувачем ===\n");
    create_temp_file_as_user(user_uid, user_gid);

    printf("\n=== Етап 2: Зміна власника та прав (через shell) ===\n");
    change_ownership_and_permissions(USERNAME);

    printf("\n=== Етап 3: Перевірка доступу як звичайний користувач ===\n");
    test_access_as_user(user_uid, user_gid);

    printf("\n=== Етап 4: Видалення файлу (root) ===\n");
    cleanup();

    printf("\n[+] Готово.\n");
    return 0;
}
