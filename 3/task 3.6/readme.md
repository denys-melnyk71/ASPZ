## Завдання:
Напишіть програму, що демонструє використання обмеження (max stack segment size). Підказка: рекурсивна програма активно використовує стек.

## Звіт:
`setrlimit(RLIMIT_STACK, &limit)` встановлює максимально дозволений розмір стеку  
Кожен виклик функції `recursive_function` виділяє 1024 байти на стеку (через `char buffer[1024]`), тому:
- чим більше глибина рекурсії, тим більше стеку спожито;
- при досягненні межі (32 КБ) виникає stack overflow.

Коли стек переповнено, ОС надсилає сигнал __SIGSEGV__, який обробляється за допомогою `signal(SIGSEGV, handler)`;

## Результат:
```
Starting recursive calls with limited stack (32 KB)...
Recursion depth: 1
Recursion depth: 2
Recursion depth: 3
Recursion depth: 4
Recursion depth: 5
Recursion depth: 6
Recursion depth: 7
Recursion depth: 8
Recursion depth: 9
Recursion depth: 10
Recursion depth: 11
Recursion depth: 12
Recursion depth: 13
Recursion depth: 14
Recursion depth: 15
Recursion depth: 16
Recursion depth: 17
Recursion depth: 18
Recursion depth: 19
Recursion depth: 20
Recursion depth: 21
Recursion depth: 22
pid 2086 comm main has trashed its stack, killing
Illegal instruction (core dumped)
```