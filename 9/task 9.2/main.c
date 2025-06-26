#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Читання /etc/master.passwd від імені адміністратора:\n");

    int ret = system("sudo cat /etc/master.passwd");

    if (ret != 0) {
        fprintf(stderr, "Не вдалося виконати команду. Можливо, потрібні права адміністратора або неправильна конфігурація sudo.\n");
        return 1;
    }

    return 0;
}
