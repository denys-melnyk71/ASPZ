#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 100000

// Функція порівняння для int
int cmp_int(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

// Функції генерації масивів
void generate_random(int *arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (n * 2);
}

void generate_sorted(int *arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = i;
}

void generate_reverse_sorted(int *arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
}

void generate_all_equal(int *arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = 42;
}

// Перевірка відсортованості
int is_sorted(int *arr, int n) {
    for (int i = 1; i < n; i++)
        if (arr[i - 1] > arr[i])
            return 0;
    return 1;
}

// Структура для зберігання результатів
typedef struct {
    const char *description;
    void (*gen_func)(int*, int);
    double time_taken;
} SortTest;

// Основна функція тестування
double test_sort(SortTest *test, int n) {
    int *arr = malloc(n * sizeof(int));
    if (!arr) { perror("malloc arr"); exit(1); }

    test->gen_func(arr, n);

    clock_t start = clock();
    qsort(arr, n, sizeof(int), cmp_int);
    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    test->time_taken = elapsed;

    if (!is_sorted(arr, n)) {
        fprintf(stderr, "ПОМИЛКА: Масив не відсортовано (%s)\n", test->description);
    }

    free(arr);
    return elapsed;
}

int main(void) {
    srand(time(NULL));
    int n = 1000000;

    SortTest tests[] = {
        {"Випадковий масив", generate_random, 0.0},
        {"Відсортований масив", generate_sorted, 0.0},
        {"Реверсно відсортований масив", generate_reverse_sorted, 0.0},
        {"Масив з однакових елементів", generate_all_equal, 0.0}
    };
    int test_count = sizeof(tests) / sizeof(tests[0]);

    printf("Тестуємо qsort з масивами розміру %d:\n", n);
    printf("-------------------------------------------\n");

    double max_time = 0.0;
    int worst_index = 0;

    for (int i = 0; i < test_count; ++i) {
        double time = test_sort(&tests[i], n);
        printf("%-30s: %.6f с\n", tests[i].description, time);

        if (time > max_time) {
            max_time = time;
            worst_index = i;
        }
    }

    printf("-------------------------------------------\n");
    printf("НАЙГІРШИЙ ВИПАДОК ДЛЯ qsort: %s (%.6f с)\n",
           tests[worst_index].description,
           tests[worst_index].time_taken);

    return 0;
}
