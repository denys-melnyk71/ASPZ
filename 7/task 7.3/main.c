#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Використання: %s <слово> <файл>\n", argv[0]);
        return 1;
    }

    const char *search_word = argv[1];
    const char *filename = argv[2];
    char line[MAX_LINE_LENGTH];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Не вдалося відкрити файл");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, search_word)) {
            printf("%s", line);
        }
    }

    fclose(file);
    return 0;
}
