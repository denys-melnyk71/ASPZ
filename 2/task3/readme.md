## Завдання:
- Скомпілюйте й запустіть тестову програму, щоб визначити приблизне
розташування стека у вашій системі:
```c
#include <stdio.h>;
int main() {
    int i;
    printf("The stack top is near %p\n", &i);
    return 0;
}
```
- Знайдіть розташування сегментів даних і тексту, а також купи всередині
сегмента даних, оголосіть змінні, які будуть поміщені в ці сегменти, і
виведіть їхні адреси.
- Збільшіть розмір стека, викликавши функцію й оголосивши кілька
великих локальних масивів. Яка зараз адреса вершини стека? 
  
__Примітка:__ стек може розташовуватися за різними адресами на різних
архітектурах та різних ОС. Хоча ми говоримо про вершину стека, на
більшості процесорів стек зростає вниз, до пам’яті з меншими значеннями
адрес.

## Звіт
Для вирішення цього завдання, мені довелось шукати інформацію щодо того де, в яких випадках і які саме дані розташовані
```
denys@ASPZ:~/PWs/ASPZ/2/task3 $ gcc main.c -o main
denys@ASPZ:~/PWs/ASPZ/2/task3 $ ./main
=== Memory Segments ===
Address of function (text segment):        0x4006a2
Address of global initialized (.data):    0x401c98
Address of global uninitialized (.bss):   0x401cac
Address of static local (.data):          0x401c9c
Address of heap variable:                 0x1a6242809000
Address of stack variable:                0x8204e2094

=== Stack Expansion Test ===
denys@ASPZ:~/PWs/ASPZ/2/task3 $ gcc main.c -o main
denys@ASPZ:~/PWs/ASPZ/2/task3 $ ./main
=== Memory Segments ===
Address of function (text segment):        0x4006a2
Address of global initialized (.data):    0x401ca0
Address of global uninitialized (.bss):   0x401cb4
Address of static local (.data):          0x401ca4
Address of heap variable:                 0x1153cda09000
Address of stack variable:                0x8213c2474

=== Stack Expansion Test ===
Address of big_array2 (stack top now):    0x8213aebe0
```