
## Варіант 12. Завдання:
Створіть daemon, який запускає зовнішній процес через задані інтервали часу, логуючи запуск і завершення.

## Звіт:

### Крок 1 - створення daemon
Створення daemon відбувається у функції daemonize()

Спершу треба створити дочірній процес
```c
pid_t pid = fork();
if (pid < 0) exit(EXIT_FAILURE);
```

Далі, виникає проблема. Дочірній процес прив'язаний до терміналу, а не працює у фоновому режимі як [daemon](https://uk.wikipedia.org/wiki/%D0%94%D0%B5%D0%BC%D0%BE%D0%BD_(%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%B0))
> Демон (англ. daemon) — сервіс Unix та Unix-подібних операційних систем, що працює у фоновому режимі без прямого спілкування з користувачем. 

Я знайшов [статтю про створення daemon](https://lloydrochester.com/post/c/unix-daemon-example/) в якій для відв'язки від терміналу рекомендується
- Завершити батьківський процес
```c
if (pid > 0) exit(EXIT_SUCCESS); // Parent exits
```
- Зробити дочірній процес лідером нової сесії
```c
setsid(); // Create new session
```
- Очистити маску дозволів
```c
umask(0); // Clear file permissions mask
```

Deamon створено. Але процес запускається в ~/PWs/ASPZ/14
```
denys@ASPZ:~/PWs/ASPZ/14 $ sudo ./main
```

Це може блокувати деякі дії з каталогом, тому краще змінити робочу директорію:
```c
chdir("/");
```

Для остаточного від'єднання від терміналу варто закрити файлові дескриптори
```c
close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);
```

### Крок 2 - реалізація логування
Для зручного запису в файл використовується dprintf
```c
void log_message(const char *message) {
    int fd = open(LOGFILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd >= 0) {
        dprintf(fd, "[%ld] %s\n", time(NULL), message);
        close(fd);
    }
}
```

### Крок 3 - створення таймеру
Щоб запускати зовнішній процес через задані інтервали часу потрібен таймер.
```c
timer_t timerid;
struct sigevent sev = {0};
sev.sigev_notify = SIGEV_SIGNAL;
sev.sigev_signo = SIGRTMIN;

if (timer_create(CLOCK_REALTIME, &sev, &timerid) == -1) {
    log_message("Failed to create timer.");
    exit(EXIT_FAILURE);
}
```
Він спрацьовуватиме кожні `INTERVAL_SEC` секунд.

Також для обробки сигналу додамо наступний код
```c
struct sigaction sa = {0};
sa.sa_flags = SA_SIGINFO;
sa.sa_sigaction = timer_handler;
sigaction(SIGRTMIN, &sa, NULL);
```
Він викликатиме функцію `timer_handler` в якій реалізований запуск зовнішнього процесу при надходжені сигналу від таймеру.

В кінці функції main() додамо очікування сигналу
```c
while (1) pause(); // Wait for signal
```

### Крок 4 - запуск зовнішнього процесу 
Для запуску зовнішнього процесу використаємо техніку описану в [статті](https://lloydrochester.com/post/c/unix-daemon-example/), відому як double fork.
> Ми знову викличемо fork(), також відомуо як double fork. Цей другий double fork зробить наш процес сиротою, оскільки батьківський процес буде завершено. Після завершення батьківського процесу дочірній процес буде прийнято початковим процесом з ідентифікатором процесу 1. Результатом другого розгалуження буде процес з батьківським процесом як початковим процесом з ідентифікатором 1. Процес буде знаходитись у власному сеансі та групі процесів і не матиме керуючого терміналу. Крім того, процес не буде лідером групи процесів, а отже, не матиме керуючого терміналу, якщо такий був.

В `timer_handler`:
```c
pid_t pid = fork();
if (pid == 0) {
    execl("/usr/bin/date", "date", NULL);
    exit(EXIT_FAILURE);
} else if (pid > 0) {
    int status;
    waitpid(pid, &status, 0);
    log_message("Process completed.");
} else {
    log_message("Failed to fork process.");
}
```

Безпосередньо запуск процесу відбувається в рядку `execl("/usr/bin/date", "date", NULL);` за допомогою функції execl(). Команда date тут вибрана чисто для прикладу, можна замінити на будь який інший процес.

### Результат:
Запускати деамон слід з правами root:
```
denys@ASPZ:~/PWs/ASPZ/14 $ sudo ./main
```

Перевіримо що процес працює:
```
denys@ASPZ:~/PWs/ASPZ/14 $ ps aux | grep main
root       2215   0.0  0.1      13956   2360  -  Ss   08:09    0:00.00 ./main
denys      2252   0.0  0.1      13920   2456  1  S+   08:11    0:00.00 grep main
```

Перевіримо чи працює логування
```
denys@ASPZ:~/PWs/ASPZ/14 $ sudo tail -f /var/log/timer_daemon.log
[1751004643] Launching external process...
[1751004643] Process completed.
[1751004653] Launching external process...
[1751004653] Process completed.
[1751004663] Launching external process...
[1751004663] Process completed.
[1751004673] Launching external process...
[1751004673] Process completed.
[1751004683] Launching external process...
[1751004683] Process completed.
[1751004693] Launching external process...
[1751004693] Process completed.
```

Зупинимо процес
```
denys@ASPZ:~/PWs/ASPZ/14 $ sudo kill 2215
```

## Висновок:
В ході виконання практичного заняття 14 мною було засвоєно навички створення daemon. запуску зовнішнього процесу з дочірнього за допомогою double fork, створення POSIX таймерів і роботи з ними.