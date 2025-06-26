#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функція для генерації випадкового числа з плаваючою точкою у [0.0, 1.0]
float random_float_0_to_1() {
    return (float)rand() / (float)RAND_MAX;
}

// Функція для генерації випадкового числа з плаваючою точкою у [0.0, n]
float random_float_0_to_n(float n) {
    return random_float_0_to_1() * n;
}

int main(void) {
    // Початкова ініціалізація генератора випадкових чисел
    srand((unsigned int)time(NULL));  // унікальна послідовність

    int count = 10; // скільки чисел згенерувати
    float n;

    printf("Введіть значення n (для генерації чисел у [0.0, n]): ");
    if (scanf("%f", &n) != 1 || n < 0.0f) {
        fprintf(stderr, "Некоректне значення n. Повинно бути дійсне число >= 0.\n");
        return 1;
    }

    printf("\n(a) Випадкові числа у [0.0, 1.0]:\n");
    for (int i = 0; i < count; ++i) {
        printf("%.6f\n", random_float_0_to_1());
    }

    printf("\n(b) Випадкові числа у [0.0, %.2f]:\n", n);
    for (int i = 0; i < count; ++i) {
        printf("%.6f\n", random_float_0_to_n(n));
    }

    return 0;
}
