## Завдання:
Побудуйте Valgrind Summary Table (таблицю), в яку включено тип помилки, приклад коду, вихід Valgrind та спосіб виправлення.

## Звіт:
Усі необхідні дані не поміщались в таблицю, тож я розписав для кожного типу помилки по пунктах
| Тип помилки                 | Приклад коду     | Вихід Valgrind | Спосіб виправлення |
|-----------------------------|------------------|----------------|--------------------|

### Memory leak     
Приклад коду:
```c
longjmp(env, 1);
```

Вихід Valgrind:
```
==1234== 64 bytes in 1 blocks are definitely lost in loss record
```

Спосіб виправлення:
```c
free(ptr); // звільнення перед longjmp
longjmp(env, 1);
```

### Use of uninitialized memory 
Приклад коду:
```c
int x;
printf("%d\n", x);
```

Вихід Valgrind:
```
==1234== Use of uninitialized value of size 4
```

Спосіб виправлення:
```c
int x = 0;
printf("%d\n", x);
```

### Invalid read/write  
Приклад коду:
```c
int* ptr = malloc(sizeof(int));
free(ptr);
int val = *ptr; 
```

Вихід Valgrind:
```
==1234== Invalid read of size 4
```

Спосіб виправлення:
```c
int* ptr = malloc(sizeof(int));
int val = *ptr;
free(ptr);
```

### Double free  
Приклад коду:
```c
char* ptr = malloc(64);
free(ptr);
free(ptr); 
```

Вихід Valgrind:
```
==1234== Invalid free() / double free()
```

Спосіб виправлення:
```c
char* ptr = malloc(64);
free(ptr);
ptr = NULL;  // запобігає подвійним free
// free(ptr);  // не виконуємо, бо ptr == NULL
```

### Mismatched free/delete  
Приклад коду:
```c
int* ptr = new int[10];
free(ptr);  // помилка: new[] слід звільняти delete[]
```
Вихід Valgrind:
```
==1234== Mismatched free/delete
```
Спосіб виправлення:
```c
//Використовувати відповідні пари `new`/`delete` або `malloc`/`free`
int* ptr = new int[10];
delete[] ptr;
```

## Висновки:
У ході виконання завдання я дізнався про тип помилки у Valgrind, відповідний їм вихід Valgrind та спосіб виправлення цих помилок.