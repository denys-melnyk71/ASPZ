## Розгляньте сегменти у виконуваному файлі.
### 1. Скомпілюйте програму &quot;hello world&quot;, запустіть ls -l для виконуваного файлу, щоб отримати його загальний розмір, і запустіть size, щоб отримати розміри сегментів всередині нього.
```
denys@ASPZ:~/PWs/ASPZ/2/task2 $ gcc subtask1.c -o subtask1
denys@ASPZ:~/PWs/ASPZ/2/task2 $ ls -l subtask1
-rwxr-xr-x  1 denys denys 8200 Jun 23 22:09 subtask1
denys@ASPZ:~/PWs/ASPZ/2/task2 $ size subtask1
   text    data     bss     dec     hex filename
   1079     552      16    1647     66f subtask1
```
### 2. Додайте оголошення глобального масиву із 1000 int, перекомпілюйте й повторіть вимірювання. Зверніть увагу на відмінності.
```
denys@ASPZ:~/PWs/ASPZ/2/task2 $ gcc subtask2.c -o subtask2
denys@ASPZ:~/PWs/ASPZ/2/task2 $ ls -l subtask2
-rwxr-xr-x  1 denys denys 8224 Jun 23 22:13 subtask2
denys@ASPZ:~/PWs/ASPZ/2/task2 $ size subtask2
   text    data     bss     dec     hex filename
   1077     552    4032    5661    161d subtask2
denys@ASPZ:~/PWs/ASPZ/2/task2 $ 
```
Видно, що глобальний масив займає `8224 - 8200 = 24` байти. Значення data не змінилось. Значення bss змінилось на `4016` байт. Це приблизно дорівнює `1000 елементів * 4 байти (int)`
### 3. Тепер додайте початкове значення в оголошення масиву (пам’ятайте, що C не змушує вас вказувати значення для кожного елемента масиву в ініціалізаторі). Це перемістить масив із сегмента BSS у сегмент даних. Повторіть вимірювання. Зверніть увагу на різницю.
```
denys@ASPZ:~/PWs/ASPZ/2/task2 $ gcc subtask3.c -o subtask3
denys@ASPZ:~/PWs/ASPZ/2/task2 $ ls -l subtask3
-rwxr-xr-x  1 denys denys 8224 Jun 23 22:17 subtask3
denys@ASPZ:~/PWs/ASPZ/2/task2 $ size subtask3
   text    data     bss     dec     hex filename
   1077     552    4032    5661    161d subtask3
denys@ASPZ:~/PWs/ASPZ/2/task2 $ 
```
Усі значення залишились незмінними. Можна зробити висновок, що масив із сегмента BSS у сегмент даних не перемістився. Можливо, треба ініціалізувати більше значень, щоб це відбулось.
### 4. Тепер додайте оголошення великого масиву в локальну функцію. Оголосіть другий великий локальний масив з ініціалізатором. Повторіть вимірювання. Дані розташовуються всередині функцій, залишаючись у виконуваному файлі? Яка різниця, якщо масив ініціалізований чи ні?
```
denys@ASPZ:~/PWs/ASPZ/2/task2 $ gcc subtask4.c -o subtask4
denys@ASPZ:~/PWs/ASPZ/2/task2 $ ls -l subtask4
-rwxr-xr-x  1 denys denys 8312 Jun 23 22:20 subtask4
denys@ASPZ:~/PWs/ASPZ/2/task2 $ size subtask4
   text    data     bss     dec     hex filename
   1165     552      16    1733     6c5 subtask4
```
Об'єм самого файлу дещо виріс, а от значення bss помітно зменшилось. Це відбувається тому, що локальні змінні зберігаються у стеку, а не виконавчому файлі.
### 5. Які зміни відбуваються з розмірами файлів і сегментів, якщо ви компілюєте для налагодження? Для максимальної оптимізації?
Для налагодження: 
```
denys@ASPZ:~/PWs/ASPZ/2/task2 $ gcc -g subtask4.c -o subtask4
denys@ASPZ:~/PWs/ASPZ/2/task2 $ ls -l subtask4
-rwxr-xr-x  1 denys denys 9088 Jun 23 22:38 subtask4
denys@ASPZ:~/PWs/ASPZ/2/task2 $ size subtask4
   text    data     bss     dec     hex filename
   1165     552      16    1733     6c5 subtask4
```
Розмір файлу збільшився майже на кілобайт.  

Для максимальної оптимізації:
```
denys@ASPZ:~/PWs/ASPZ/2/task2 $ gcc -O3 subtask4.c -o subtask4
denys@ASPZ:~/PWs/ASPZ/2/task2 $ ls -l subtask4
-rwxr-xr-x  1 denys denys 8272 Jun 23 22:39 subtask4
denys@ASPZ:~/PWs/ASPZ/2/task2 $ size subtask4
   text    data     bss     dec     hex filename
   1124     552      16    1692     69c subtask4
```
Розмір файлу а також значення dec дещо менші.