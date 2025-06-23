#include <stdio.h>
#include <time.h>

int main() {
    time_t time;
    size_t time_size = sizeof(time);

    printf("Розмір типу time_t = %zu байт\n", time_size);

    if (time_size == 4) {
        printf("Використовується 32-бітна архітектура");
    } else {
        printf("Використовується 64-бітна архітектура");
    }

    return 0;
}

