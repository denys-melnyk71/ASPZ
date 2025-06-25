## Завдання:
Напишіть програму для копіювання одного іменованого файлу в інший. Імена файлів передаються у вигляді аргументів.
Програма має:
- перевіряти, чи передано два аргументи, інакше виводити "Program need two arguments";
- перевіряти доступність першого файлу для читання, інакше виводити "Cannot open file .... for reading";
- перевіряти доступність другого файлу для запису, інакше виводити "Cannot open file .... for writing";
- обробляти ситуацію перевищення обмеження на розмір файлу.


## Звіт:
Перевірка обмеження на розмір файлу (RLIMIT_FSIZE) відбувається за допомогою `getrlimit(RLIMIT_FSIZE, &lim)`  

При досягненні ліміту система може повертати помилку EFBIG при write().
Рішення: перевіряв errno після помилки запису, щоб вивести відповідне повідомлення.
```
if (errno == EFBIG) {
    fprintf(stderr, "File size limit exceeded. Write failed.\n");
}
```

Запуск програми без аргументів
```
denys@ASPZ:~/PWs/ASPZ/3/task 3.5 $ gcc main.c -o copyfile
denys@ASPZ:~/PWs/ASPZ/3/task 3.5 $ ./copyfile 
Program need two arguments
```
Заруск до створення файлів file1.txt та file2.txt
```
denys@ASPZ:~/PWs/ASPZ/3/task 3.5 $ ./copyfile file1.txt file2.txt
Cannot open file file1.txt for reading
```
