#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int xa = 100000;
    int xb = 100000;
    int num = xa * xb; // 100000 * 100000 = 10,000,000,000 > INT_MAX (2,147,483,647)

    printf("xa = %d, xb = %d, num = %d\n", xa, xb, num);

    void *ptr = malloc(num);
    if (ptr == NULL) {
        perror("malloc");
    } else {
        printf("malloc succeeded (unexpected)\n");
        free(ptr);
    }

    return 0;
}
