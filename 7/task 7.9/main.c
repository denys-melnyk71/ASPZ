#include <stdio.h>
#include <time.h>

int main() {
    // Змінні для збереження часу початку та кінця
    clock_t start_time, end_time;
    double time_taken;

    // Початок вимірювання часу
    start_time = clock();

    // === ФРАГМЕНТ КОДУ, ЧАС ЯКОГО МІРЯЄМО ===
    // Наприклад, проста затримка через цикл
    volatile long long sum = 0;
    for (long long i = 0; i < 100000000; ++i) {
        sum += i;
    }
    // =========================================

    // Кінець вимірювання часу
    end_time = clock();

    // Обчислення часу у мілісекундах
    time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0;

    // Вивід результату
    printf("Час виконання: %.3f мс\n", time_taken);

    return 0;
}
