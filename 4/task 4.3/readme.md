## Завдання:
Що станеться, якщо використати malloc(0)? Напишіть тестовий випадок, у якому malloc(3) повертає NULL або вказівник, що не є NULL, і який можна передати у free(). Відкомпілюйте та запустіть через ltrace. Поясніть поведінку програми.

## Звіт:
На [alloc(3) — Linux manual page](https://man7.org/linux/man-pages/man3/free.3.html) я знайшов, що:
> Якщо розмір
 дорівнює 0, то malloc() повертає унікальне значення вказівника, яке пізніше можна
 успішно передати у free().

Запуск через ltrace:
```
denys@ASPZ:~/PWs/ASPZ/4/task 4.3 $ ltrace ./main
Couldn't determine base address of [vdso]
Couldn't load ELF object [vdso]: No such file or directory
__libc_start1(1, 0x820da5048, 0x820da5058, 0x1e61efd27cc0, 0x400652 <unfinished ...>
malloc(0)                                                            = 0x2cd207c08008
printf("malloc(0) \320\277\320\276\320\262"...malloc(0) повернуло адресу: 0x2cd207c08008
)                      = 58
free(0x2cd207c08008)                                                 = <void>
+++ exited (status 0) +++
denys@ASPZ:~/PWs/ASPZ/4/task 4.3 $
```
Пояснення поведінки програми:

malloc повернув не-NULL вказівник, а 0x2cd207c08008. Пам’ять, виділена malloc(0), була успішно звільнена.