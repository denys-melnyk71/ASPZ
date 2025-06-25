#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int x;
    char data[32];
};

int main() {
    struct sbar *ptr, *newptr;

    ptr = calloc(1000, sizeof(struct sbar));
    if (!ptr) {
        perror("calloc");
        return 1;
    }

    newptr = reallocarray(ptr, 500, sizeof(struct sbar));
    if (!newptr) {
        perror("reallocarray");
        free(ptr); // важливо: старий вказівник залишається дійсним
        return 1;
    }

    ptr = newptr;
    free(ptr);

    return 0;
}
