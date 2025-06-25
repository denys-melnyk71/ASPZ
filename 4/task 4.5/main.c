#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t initial_size = 1024;           // 1 KB
    size_t huge_size = (size_t)-1;        // найбільше можливе значення

    char *ptr = malloc(initial_size);
    if (!ptr) {
        perror("Initial malloc failed");
        return 1;
    }

    printf("Initial allocation successful: %p\n", ptr);

    char *tmp = realloc(ptr, huge_size);  // пробуємо розширити до гігантського розміру

    if (!tmp) {
        perror("realloc failed");         // Очікувано: не вистачає памʼяті
        printf("Pointer still valid: %p\n", ptr); // ptr все ще вказує на початковий блок
        free(ptr);  // важливо не забути звільнити!
    } else {
        ptr = tmp;
        printf("Realloc succeeded unexpectedly: %p\n", ptr);
        free(ptr);
    }

    return 0;
}
