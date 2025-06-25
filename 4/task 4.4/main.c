#include <stdio.h>
#include <stdlib.h>

int main() {
    const int iterations = 3;
    const size_t size = 32; // виділимо 32 байти на кожну ітерацію

    for (int i = 0; i < iterations; i++) {
        void *ptr = malloc(size);
        if (!ptr) {
            perror("malloc failed");
            return 1;
        }

        printf("Iteration %d: Allocated memory at %p\n", i + 1, ptr);

        // Імітуємо використання пам’яті
        ((char *)ptr)[0] = 'A';

        free(ptr);
        printf("Iteration %d: Memory at %p freed\n\n", i + 1, ptr);
        // Не потрібно обнуляти ptr, бо він зникає після ітерації
    }

    return 0;
}
