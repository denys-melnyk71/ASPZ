#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>

jmp_buf env;

// Обробник сигналу — моделює "раптову зупинку"
void handle_signal(int sig) {
    printf("\n[!] Отримано сигнал: %d — вихід через longjmp\n", sig);
    longjmp(env, 2);  // Перериває нормальне виконання без free()
}

// Функція, що виділяє пам’ять і може втратити її
void allocate_and_maybe_fail() {
    int *buffer = (int *)malloc(100 * sizeof(int));
    if (!buffer) {
        printf("[-] Не вдалося виділити пам’ять\n");
        return;
    }

    printf("[+] Пам’ять успішно виділена\n");

    // Симулюємо сигнал (натисни Ctrl+C під час виконання або активуй raise(SIGINT))
    printf("[~] Очікую на Ctrl+C або продовження...\n");
    for (volatile int i = 1; i < 6; ++i) { // Просто затримка
        printf("%i/5\n", i);
        sleep(1);
    } 

    // У звичайному випадку пам’ять звільняється
    free(buffer);
    printf("[+] Пам’ять звільнена нормально\n");
}

int main() {
    // Встановлюємо обробник сигналу
    signal(SIGINT, handle_signal);

    int jmp_code = setjmp(env);
    if (jmp_code == 0) {
        printf("[*] Початок роботи\n");
        allocate_and_maybe_fail();
    } else if (jmp_code == 2) {
        printf("[!] Вийшли з обробника сигналу без вивільнення пам’яті (витік)\n");
    }

    printf("[*] Завершення програми\n");
    return 0;
}
