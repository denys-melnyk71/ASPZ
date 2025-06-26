#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pwd.h>
#include <errno.h>

#define USERNAME "denys" 
#define USER_FILE "/tmp/userfile.txt"
#define DEST_FILE "/home/denys/copied_by_root.txt"  
#define BUF_SIZE 1024

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

void write_as_user(uid_t uid, gid_t gid) {
    drop_privileges(uid, gid);
    printf("[User] Створюємо файл: %s\n", USER_FILE);

    FILE *f = fopen(USER_FILE, "w");
    if (!f) error_exit("fopen user file");

    fprintf(f, "Це тестовий файл, створений користувачем UID=%d\n", uid);
    fclose(f);
    printf("[User] Файл створено.\n");

    restore_privileges();
}

void copy_as_root(uid_t user_uid, gid_t user_gid) {
    printf("[Root] Копіюємо %s до %s\n", USER_FILE, DEST_FILE);

    int src = open(USER_FILE, O_RDONLY);
    if (src == -1) error_exit("open src");

    int dst = open(DEST_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (dst == -1) error_exit("open dst");

    char buf[BUF_SIZE];
    ssize_t bytes;
    while ((bytes = read(src, buf, BUF_SIZE)) > 0) {
        if (write(dst, buf, bytes) != bytes) error_exit("write");
    }
    if (bytes == -1) error_exit("read");

    close(src);
    close(dst);

    if (chown(DEST_FILE, user_uid, user_gid) != 0)
        error_exit("chown");

    if (chmod(DEST_FILE, S_IRUSR | S_IWUSR) != 0)
        error_exit("chmod");

    printf("[Root] Копіювання завершено. Власник: UID=%d, права: rw-------\n", user_uid);
}

void modify_file_as_user(uid_t uid, gid_t gid) {
    drop_privileges(uid, gid);
    printf("[User] Спроба змінити файл %s\n", DEST_FILE);

    FILE *f = fopen(DEST_FILE, "a");
    if (!f) {
        perror("[User] Не вдалося відкрити файл для допису");
    } else {
        fprintf(f, "Цей рядок додано користувачем UID=%d\n", uid);
        fclose(f);
        printf("[User] Зміни збережено успішно.\n");
    }

    restore_privileges();
}

void delete_file_as_user(uid_t uid, gid_t gid) {
    drop_privileges(uid, gid);
    printf("[User] Спроба видалити файл %s за допомогою команди rm\n", DEST_FILE);

    char command[BUF_SIZE];
    snprintf(command, sizeof(command), "rm '%s'", DEST_FILE);

    int ret = system(command);
    if (ret == 0) {
        printf("[User] Файл успішно видалено командою rm.\n");
    } else {
        fprintf(stderr, "[User] Помилка при видаленні файлу командою rm (код: %d)\n", ret);
    }

    restore_privileges();
}


int main() {
    if (geteuid() != 0) {
        fprintf(stderr, "⚠️ Ця програма повинна бути запущена з правами root.\n");
        return 1;
    }

    struct passwd *pw = getpwnam(USERNAME);
    if (!pw) error_exit("getpwnam");

    uid_t user_uid = pw->pw_uid;
    gid_t user_gid = pw->pw_gid;

    printf("=== Етап 1: Створення файлу користувачем ===\n");
    write_as_user(user_uid, user_gid);

    printf("\n=== Етап 2: Копіювання файлу від імені root ===\n");
    copy_as_root(user_uid, user_gid);

    printf("\n=== Етап 3: Модифікація файлу як користувач ===\n");
    modify_file_as_user(user_uid, user_gid);

    printf("\n=== Етап 4: Видалення файлу як користувач ===\n");
    delete_file_as_user(user_uid, user_gid);

    printf("\n[+] Готово.\n");
    return 0;
}
