#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int x;
    char data[32];
};

int main() {
    struct sbar *ptr, *newptr;

    // Виділення пам’яті для 1000 елементів
    ptr = calloc(1000, sizeof(struct sbar));
    if (!ptr) {
        perror("calloc failed");
        return 1;
    }
    printf("calloc: %p (1000 елементів)\n", (void *)ptr);

    // Перевиділення для 500 елементів
    newptr = realloc(ptr, 500 * sizeof(struct sbar));
    if (!newptr) {
        perror("realloc failed");
        free(ptr);  // звільняємо стару пам’ять
        return 1;
    }

    printf("realloc: %p (500 елементів)\n", (void *)newptr);

    // Звільняємо пам'ять
    free(newptr);

    return 0;
}
