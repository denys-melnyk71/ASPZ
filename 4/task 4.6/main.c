#include <stdio.h>
#include <stdlib.h>

int main() {
    // 1. realloc з NULL
    printf("Calling realloc(NULL, 128)...\n");
    void *p1 = realloc(NULL, 128);
    if (p1)
        printf("Success: allocated at %p\n", p1);
    else
        perror("realloc(NULL, 128) failed");

    // 2. realloc з існуючим блоком і розміром 0
    printf("\nCalling realloc(p1, 0)...\n");
    void *p2 = realloc(p1, 0);
    if (p2 == NULL)
        printf("realloc(p1, 0) returned NULL (memory freed)\n");
    else
        printf("Unexpected: realloc(p1, 0) returned %p\n", p2); // не має статися

    // 3. realloc(NULL, 0)
    printf("\nCalling realloc(NULL, 0)...\n");
    void *p3 = realloc(NULL, 0);
    if (p3 == NULL)
        printf("realloc(NULL, 0) returned NULL (implementation-defined)\n");
    else {
        printf("realloc(NULL, 0) returned %p (must free!)\n", p3);
        free(p3);
    }

    return 0;
}
