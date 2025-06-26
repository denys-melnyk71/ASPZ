#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>
#include <string.h>

int main(void) {
    // Встановлюємо локаль для коректного форматування дати/часу
    setlocale(LC_ALL, "");

    time_t now = time(NULL);
    char time_str[64] = {0}; // ініціалізуємо буфер нулями

    // Форматуємо час у вигляді "YYYY-MM-DD HH:MM:SS"
    if (strftime(time_str, sizeof(time_str), "%F %T", localtime(&now)) == 0) {
        // Якщо буфер замалий або помилка — виводимо дефолтне значення
        strcpy(time_str, "unknown time");
    }

    // Відкриваємо з'єднання з syslog
    openlog("MyFreeBSDProgram", LOG_PID | LOG_CONS, LOG_USER);

    // Запис у системний журнал
    syslog(LOG_INFO, "Programm started by user with PID %d at %s", getpid(), time_str);

    // Закриваємо з'єднання
    closelog();

    printf("Програма працює...\n");

    return 0;
}
