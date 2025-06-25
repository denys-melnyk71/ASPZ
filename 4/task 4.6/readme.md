## Завдання:
Якщо realloc(3) викликати з NULL або розміром 0, що станеться? Напишіть тестовий випадок.

## Звіт:
Згідно [realloc(3p) — Linux manual page](https://man7.org/linux/man-pages/man3/realloc.3p.html) 
>Якщо
 розмір запитуваного простору дорівнює нулю, поведінка має бути
 визначена реалізацією: або повертається нульовий вказівник, або
 поведінка має бути такою, як якщо б розмір був деяким ненульовим значенням, за винятком
 того, що поведінка є невизначеною, якщо повернутий вказівник використовується для
 доступу до об'єкта.

 >Якщо ptr є нульовим вказівником, realloc() буде еквівалентний
 malloc() для вказаного розміру.

 ### Результат:
 ```
denys@ASPZ:~/PWs/ASPZ/4/task 4.6 $ ./main
Calling realloc(NULL, 128)...
Success: allocated at 0x396cdfc13000

Calling realloc(p1, 0)...
Unexpected: realloc(p1, 0) returned 0x396cdfc08008

Calling realloc(NULL, 0)...
realloc(NULL, 0) returned 0x396cdfc08010 (must free!)
 ```