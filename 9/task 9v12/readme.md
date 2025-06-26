## Завдання:
Дослідіть поведінку fork() у випадку, коли системні ресурси обмежено. Як змінюється вихід?

## Звіт:
Перевіримо обмеження
```
denys@ASPZ:~/PWs/ASPZ/9/task 9v12 $ ulimit -a
cpu time               (seconds, -t)  unlimited
file size           (512-blocks, -f)  unlimited
data seg size           (kbytes, -d)  33554432
stack size              (kbytes, -s)  524288
core file size      (512-blocks, -c)  unlimited
max memory size         (kbytes, -m)  unlimited
locked memory           (kbytes, -l)  131072
max user processes              (-u)  8499
open files                      (-n)  116964
virtual mem size        (kbytes, -v)  unlimited
swap limit              (kbytes, -w)  unlimited
socket buffer size       (bytes, -b)  unlimited
pseudo-terminals                (-p)  unlimited
kqueues                         (-k)  unlimited
umtx shared locks               (-o)  unlimited
pipebuf                         (-y)  unlimited
```

звернемо увагу на рядок 
```
max user processes              (-u)  8499
```

Виконаємо програму
```
denys@ASPZ:~/PWs/ASPZ/9/task 9v12 $ ./main
fork failed: Resource temporarily unavailable
Створено процесів: 8421
```

Зменшимо ліміт
```
denys@ASPZ:~/PWs/ASPZ/9/task 9v12 $ ulimit -u 100
```

Виконаємо програму знову
```
denys@ASPZ:~/PWs/ASPZ/9/task 9v12 $ ./main
fork failed: Resource temporarily unavailable
Створено процесів: 22
```

Програма створює на 78 процесів менше ніж максимально дозволено в обох випадках. Це може вказувати на те що 78 процесів уже виконуються.