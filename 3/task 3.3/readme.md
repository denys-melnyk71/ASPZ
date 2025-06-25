## Завдання:
Напишіть програму, що імітує кидання шестигранного кубика. Імітуйте кидки, результати записуйте у файл, для якого попередньо встановлено обмеження на його максимальний розмір (max file size). Коректно обробіть ситуацію перевищення ліміту.
## Звіт:
Функція `is_over_limit()` перевіряє, чи перевищує файл `dice_log.txt` розмір 128 байт.  

Якщо ліміт перевищено, функція `prompt_clear()` виводить запит до користувача з пропозицією очистити файл. У разі відмови — програма завершує роботу.  


```
denys@ASPZ:~/PWs/ASPZ/3/task 3.3 $ ./main
Dice roller active. ^C to quit.
Rolled: 6
Rolled: 6
Rolled: 4
Rolled: 6
Rolled: 2
Rolled: 2
Rolled: 1
Rolled: 6
Rolled: 3
Rolled: 2
Rolled: 2
Rolled: 5
Rolled: 3
Log file too big (128 bytes). Clear it and continue? [y/N]: y
Log reset.
Rolled: 5
Rolled: 2
Rolled: 2
Rolled: 1
Rolled: 1
Rolled: 3
Rolled: 1
Rolled: 6
Rolled: 2
Rolled: 6
Rolled: 5
Rolled: 1
Rolled: 2
Log file too big (128 bytes). Clear it and continue? [y/N]: N
Stopping.
```
