#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <elf.h>
#include <unistd.h>
#include <sys/types.h>

// Перевірка ELF
int is_elf(const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) return 0;

    Elf64_Ehdr hdr;
    fread(&hdr, 1, sizeof(hdr), f);
    fclose(f);

    return (memcmp(hdr.e_ident, ELFMAG, SELFMAG) == 0);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Використання: %s <elf-файл> [аргументи]\n", argv[0]);
        return 1;
    }

    if (!is_elf(argv[1])) {
        fprintf(stderr, "Це не ELF-файл або його не можна прочитати.\n");
        return 1;
    }

    printf("Файл %s виглядає як ELF. Запускаємо...\n", argv[1]);

    // Підготовка аргументів для execve
    char** new_argv = &argv[1];
    execv(argv[1], new_argv);  // execv замінює поточний процес

    perror("execv не вдалося");
    return 1;
}
