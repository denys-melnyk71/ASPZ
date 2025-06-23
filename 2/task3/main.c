#include <stdio.h>
#include <stdlib.h>

// Глобальні змінні
int global_initialized = 42;     // Сегмент .data
int global_uninitialized;        // Сегмент .bss

void code_segment_func() { }     // Текстовий сегмент (code)
void stack_test();

int main() {
    int local_var = 1;           // Стек
    static int static_var = 2;   // Сегмент .data

    int *heap_var = malloc(sizeof(int) * 10);  // Куча (heap)
    if (!heap_var) {
        perror("malloc");
        return 1;
    }

    printf("=== Memory Segments ===\n");
    printf("Address of function (text segment):        %p\n", (void*)code_segment_func);
    printf("Address of global initialized (.data):    %p\n", (void*)&global_initialized);
    printf("Address of global uninitialized (.bss):   %p\n", (void*)&global_uninitialized);
    printf("Address of static local (.data):          %p\n", (void*)&static_var);
    printf("Address of heap variable:                 %p\n", (void*)heap_var);
    printf("Address of stack variable:                %p\n", (void*)&local_var);

    // Дослідження зміщення вершини стека
    printf("\n=== Stack Expansion Test ===\n");
    stack_test();

    free(heap_var);
    return 0;
}

void stack_test() {
    int big_array1[10000];
    int big_array2[10000];
    printf("Address of big_array2 (stack top now):    %p\n", (void*)&big_array2);
}
