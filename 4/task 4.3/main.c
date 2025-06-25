#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = malloc(0);

    if (ptr == NULL) {
        printf("malloc(0) повернуло NULL\n");
    } else {
        printf("malloc(0) повернуло адресу: %p\n", ptr);
    }

    free(ptr);  // Завжди безпечно викликати
    return 0;
}
