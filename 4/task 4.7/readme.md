## Завдання:
Перепишіть наступний код, використовуючи reallocarray(3):
 ```
struct sbar *ptr, *newptr;
ptr = calloc(1000, sizeof(struct sbar));
newptr = realloc(ptr, 500*sizeof(struct sbar));
 ```

Порівняйте результати виконання з використанням ltrace.

## Звіт:

### Результат:
 ```
denys@ASPZ:~/PWs/ASPZ/4/task 4.7 $ ltrace ./old
Couldn't determine base address of [vdso]
Couldn't load ELF object [vdso]: No such file or directory
__libc_start1(1, 0x820a63248, 0x820a63258, 0xa50ebdfccc0, 0x4006a2 <unfinished ...>
calloc(1000, 36)                                                     = 0x374f4f809a80
printf("calloc: %p (1000 \320\265\320\273"..., 0x374f4f809a80calloc: 0x374f4f809a80 (1000 елементів)
)       = 49
realloc(0x374f4f809a80, 18000)                                       = 0x374f4f809a80
printf("realloc: %p (500 \320\265\320\273"..., 0x374f4f809a80realloc: 0x374f4f809a80 (500 елементів)
)       = 49
free(0x374f4f809a80)                                                 = <void>
+++ exited (status 0) +++
```
```
denys@ASPZ:~/PWs/ASPZ/4/task 4.7 $ ltrace ./new
Couldn't determine base address of [vdso]
Couldn't load ELF object [vdso]: No such file or directory
__libc_start1(1, 0x820a52140, 0x820a52150, 0x3ddbce81acc0, 0x400682 <unfinished ...>
calloc(1000, 36)                                                     = 0x38ecaee09880
reallocarray(0x38ecaee09880, 500, 36, 0xc03992207a946dbd, 13)        = 0x38ecaee09880
free(0x38ecaee09880)                                                 = <void>
+++ exited (status 0) +++
 ```

### Порівняння:
- В обох випадках calloc(1000, 36) викликається й повертає дійсну адресу
- В обох випадках виділена адреса залишається незмінною після realloc/reallocarray, тобто перевиділення пройшло без переміщення.

Загалом нічого не змінилось.
