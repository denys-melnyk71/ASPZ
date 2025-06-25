#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 1000000

int main() {
    int *arr_calloc, *arr_malloc;
    clock_t start, end;
    double time_calloc, time_malloc;

    // Тестування calloc
    start = clock();
    arr_calloc = (int *)calloc(SIZE, sizeof(int));
    end = clock();
    time_calloc = (double)(end - start) / CLOCKS_PER_SEC;

    // Перевірка правильності ініціалізації
    int errors_calloc = 0;
    for (size_t i = 0; i < SIZE; ++i) {
        if (arr_calloc[i] != 0) {
            errors_calloc++;
            break;
        }
    }

    // Тестування malloc + memset
    start = clock();
    arr_malloc = (int *)malloc(SIZE * sizeof(int));
    if (arr_malloc != NULL) {
        memset(arr_malloc, 0, SIZE * sizeof(int));
    }
    end = clock();
    time_malloc = (double)(end - start) / CLOCKS_PER_SEC;

    // Перевірка правильності ініціалізації
    int errors_malloc = 0;
    for (size_t i = 0; i < SIZE; ++i) {
        if (arr_malloc[i] != 0) {
            errors_malloc++;
            break;
        }
    }

    // Вивід результатів
    printf("calloc: %.6f сек. (помилки: %d)\n", time_calloc, errors_calloc);
    printf("malloc + memset: %.6f сек. (помилки: %d)\n", time_malloc, errors_malloc);

    // Звільнення пам’яті
    free(arr_calloc);
    free(arr_malloc);

    return 0;
}
