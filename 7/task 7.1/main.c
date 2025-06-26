#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char buffer[256];

    // Виконуємо команду rwho через popen
    fp = popen("rwho", "r");
    if (fp == NULL) {
        perror("popen failed");
        return 1;
    }

    // Відкриваємо another pipe для more
    FILE *more = popen("more", "w");
    if (more == NULL) {
        perror("popen more failed");
        pclose(fp);
        return 1;
    }

    // Зчитуємо з rwho і передаємо у more
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, more);
    }

    // Закриваємо обидва процеси
    pclose(fp);
    pclose(more);

    return 0;
}
