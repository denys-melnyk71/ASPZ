## Завдання:
Напишіть програму, яка виводить список файлів, заданих у вигляді аргументів, з зупинкою кожні 20 рядків, доки не буде натиснута клавіша (спрощена версія утиліти more в UNIX).

## Звіт:
[more](https://uk.wikipedia.org/wiki/More) - програма в UNIX-подібних операційних системах, що використовується для проглядання вмісту текстових файлів. На відміну від less, more виводить вміст файлу на екран окремими сторінками. Для переходу на наступну сторінку використовується клавіша пробілу.

В моїй версії програми пробіл замінено на Enter.

Виконання програми без аргументів:
```
denys@ASPZ:~/PWs/ASPZ/7/task 7.4 $ ./main
Використання: ./main <файл1> <файл2> ...
```

Виконання програми з аргументами (тільки частина виводу, зі зрозумілих причин):
```
denys@ASPZ:~/PWs/ASPZ/7/task 7.4 $ ./main file1.txt file2.txt

=== Вміст файлу: file1.txt ===

more command in Linux with Examples
Last Updated : 02 Sep, 2024

The 'more' command in Linux is a useful tool for viewing text files in the command 
prompt, particularly when dealing with large files like log files. It displays the 
ontent one screen at a time, allowing users to scroll through the text easily. 
This command is especially handy for reviewing long outputs and can be combined with 
other commands using pipes.

Here, we’ll explore the various functionalities of the more command, including its 
syntax, options, and practical examples.
What is the 'more' Command?

The 'more' command is a basic pager program used in Unix-like systems to view text 
files in the command line interface. It provides a convenient way to navigate through 
files one screenful at a time, making it ideal for reading lengthy files without 
overwhelming the terminal with all the content at once.
Syntax:


-- натисніть Enter для продовження --
```
