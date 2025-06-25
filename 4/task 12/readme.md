## Завдання:
Напишіть тест на використання calloc у порівнянні з malloc + memset.


## Звіт:

`calloc(n, size)` виділяє пам’ять і автоматично ініціалізує її нулями. - [calloc(3p) — Linux manual page](https://man7.org/linux/man-pages/man3/calloc.3p.html)

`malloc(n * size)` виділяє, але не ініціалізує пам’ять.

`memset(ptr, 0, n * size)` явно ініціалізує пам’ять нулями після malloc - [memset(3) — Linux manual page](https://man7.org/linux/man-pages/man3/memset.3.html)

### Результат:
```
denys@ASPZ:~/PWs/ASPZ/4/task 12 $ ./main
calloc: 0.000000 сек. (помилки: 0)
malloc + memset: 0.000000 сек. (помилки: 0)
```