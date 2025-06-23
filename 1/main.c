#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 20

// Функції порівняння
int compare_int(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}
int compare_float(const void* a, const void* b) {
    float diff = (*(float*)a - *(float*)b);
    return (diff > 0) - (diff < 0);
}
int compare_char(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}

// Рекурсивний лінійний пошук
int recursive_search(void* arr, void* key, size_t size, int index, int total, int (*cmp)(const void*, const void*)) {
    if (index >= total) return -1;
    if (cmp((char*)arr + index * size, key) == 0)
        return index;
    return recursive_search(arr, key, size, index + 1, total, cmp);
}

// Рекурсивний бінарний пошук
int binary_search(void* arr, void* key, int low, int high, size_t size, int (*cmp)(const void*, const void*)) {
    if (low > high) return -1;
    int mid = (low + high) / 2;
    void* mid_elem = (char*)arr + mid * size;
    int result = cmp(mid_elem, key);
    if (result == 0)
        return mid;
    else if (result > 0)
        return binary_search(arr, key, low, mid - 1, size, cmp);
    else
        return binary_search(arr, key, mid + 1, high, size, cmp);
}

// Заповнення випадковими значеннями
void fill_random(void* arr, size_t size, int count, const char* type) {
    for (int i = 0; i < count; i++) {
        if (strcmp(type, "int") == 0)
            *((int*)arr + i) = rand() % 100;
        else if (strcmp(type, "float") == 0)
            *((float*)arr + i) = (float)(rand() % 1000) / 10.0;
        else if (strcmp(type, "char") == 0)
            *((char*)arr + i) = 'A' + rand() % 26;
    }
}

// Вивід масиву
void print_array(void* arr, const char* type, int count) {
    printf("Масив: ");
    for (int i = 0; i < count; i++) {
        if (strcmp(type, "int") == 0)
            printf("%d ", *((int*)arr + i));
        else if (strcmp(type, "float") == 0)
            printf("%.1f ", *((float*)arr + i));
        else if (strcmp(type, "char") == 0)
            printf("%c ", *((char*)arr + i));
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2 || 
        (strcmp(argv[1], "int") != 0 && strcmp(argv[1], "float") != 0 && strcmp(argv[1], "char") != 0)) {
        printf("Використання: %s [int|float|char]\n", argv[0]);
        return 1;
    }

    srand((unsigned int)time(NULL));
    const char* type = argv[1];
    void* array = NULL;
    size_t size;
    int (*cmp)(const void*, const void*);

    if (strcmp(type, "int") == 0) {
        array = malloc(SIZE * sizeof(int));
        size = sizeof(int);
        cmp = compare_int;
    } else if (strcmp(type, "float") == 0) {
        array = malloc(SIZE * sizeof(float));
        size = sizeof(float);
        cmp = compare_float;
    } else if (strcmp(type, "char") == 0) {
        array = malloc(SIZE * sizeof(char));
        size = sizeof(char);
        cmp = compare_char;
    }

    fill_random(array, size, SIZE, type);
    print_array(array, type, SIZE);

    // Пошук елемента
    char input[100];
    printf("Введіть значення для пошуку: ");
    fgets(input, sizeof(input), stdin);

    void* key = malloc(size);
    if (strcmp(type, "int") == 0)
        *((int*)key) = atoi(input);
    else if (strcmp(type, "float") == 0)
        *((float*)key) = atof(input);
    else if (strcmp(type, "char") == 0)
        *((char*)key) = input[0];

    int index = recursive_search(array, key, size, 0, SIZE, cmp);
    if (index != -1)
        printf("Значення знайдено під індексом %d (лінійний пошук)\n", index);
    else
        printf("Значення не знайдено (лінійний пошук)\n");

    qsort(array, SIZE, size, cmp);
    print_array(array, type, SIZE);

    int index_bin = binary_search(array, key, 0, SIZE - 1, size, cmp);
    if (index_bin != -1)
        printf("Значення знайдено під індексом %d (бінарний пошук)\n", index_bin);
    else
        printf("Значення не знайдено (бінарний пошук)\n");

    free(array);
    free(key);
    return 0;
}
