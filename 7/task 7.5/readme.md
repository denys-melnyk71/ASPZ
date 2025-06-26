## Завдання:
Напишіть програму, яка перелічує всі файли в поточному каталозі та всі файли в підкаталогах.

## Звіт:
Про stat() та readdir() я вже знав з попередніх завдан.
Для формування повного шляху файлів/каталогів використовується snprintf.

```
denys@ASPZ:~/PWs/ASPZ/7 $ "./task 7.5/main"
[DIR]  ./task 7.1
       ./task 7.1/main.c
       ./task 7.1/readme.md
       ./task 7.1/main
[DIR]  ./task 7.2
       ./task 7.2/main.c
       ./task 7.2/readme.md
       ./task 7.2/main
       ./readme.md
[DIR]  ./task 7.4
       ./task 7.4/main.c
       ./task 7.4/readme.md
       ./task 7.4/file1.txt
       ./task 7.4/file2.txt
       ./task 7.4/main
[DIR]  ./task 7.5
       ./task 7.5/main.c
       ./task 7.5/readme.md
       ./task 7.5/main
[DIR]  ./task 7.6
       ./task 7.6/main.c
       ./task 7.6/readme.md
[DIR]  ./task 7.7
       ./task 7.7/main.c
       ./task 7.7/readme.md
[DIR]  ./task 7.8
       ./task 7.8/main.c
       ./task 7.8/readme.md
[DIR]  ./task 7.10
       ./task 7.10/main.c
       ./task 7.10/readme.md
[DIR]  ./task 7v12
       ./task 7v12/main.c
       ./task 7v12/readme.md
[DIR]  ./task 7.3
       ./task 7.3/main.c
       ./task 7.3/readme.md
       ./task 7.3/file.txt
       ./task 7.3/main
[DIR]  ./task 7.9
       ./task 7.9/main.c
       ./task 7.9/readme.md
```
