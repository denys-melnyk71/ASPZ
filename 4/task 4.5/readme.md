## Завдання:
Що станеться, якщо realloc(3) не зможе виділити пам’ять? Напишіть тестовий випадок, що демонструє цей сценарій.

## Звіт:
Згідно [realloc(3p) — Linux manual page](https://man7.org/linux/man-pages/man3/realloc.3p.html) 
>Якщо місце не може бути виділено, об'єкт
 залишиться незмінним.

### Результат:
 ```
denys@ASPZ:~/PWs/ASPZ/4/task 4.5 $ ./main
Initial allocation successful: 0x3b29cb009000
realloc failed: Cannot allocate memory
Pointer still valid: 0x3b29cb009000
 ```