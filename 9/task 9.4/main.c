#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== Перевірка облікового запису користувача ===\n");

    printf("\n[1] Команда `whoami` показує поточного користувача:\n");
    int ret1 = system("whoami");
    if (ret1 != 0) {
        fprintf(stderr, "Помилка виконання whoami\n");
    }

    printf("\n[2] Команда `id` показує UID, GID і групи користувача:\n");
    int ret2 = system("id");
    if (ret2 != 0) {
        fprintf(stderr, "Помилка виконання id\n");
    }

    printf("\n[+] Готово.\n");
    return 0;
}
