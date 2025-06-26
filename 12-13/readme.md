
## Варіант 12. Завдання:
Розробіть систему публікації-підписки, де кілька підписників слухають сигнали з різними пріоритетами, використовуючи SIGRTMIN + N.

## Звіт:
Загальна ідея
- Кожен підписник запускається у своєму процесі та слухає визначений сигнал реального часу (наприклад, SIGRTMIN+1).                                                          
- Видавець (publisher) надсилає сигнали через sigqueue() з payload (наприклад, номер повідомлення).

В subscriber.c 
- реалізовано handler для обробки сигналу від publisher
- очікується 1 аргумент командного рядка: offset 
```c
int offset = atoi(argv[1]);
```
- використовуємо sigaction() замість signal() для підтримки додаткової інформації (siginfo_t).
- реалізовано очікування сигналу
```c
while (1) pause();
```

В publisher.c сигнал формується та надсилається:
```c
int signo = SIGRTMIN + offset;

union sigval val;
val.sival_int = value;

if (sigqueue(pid, signo, val) == -1) {
    perror("sigqueue failed");
    return 1;
}
```

### Результат:
Створимо два процеси підписники

Subscriber 1:
```
denys@ASPZ:~/PWs/ASPZ/12-13 $ ./subscriber 1
[Subscriber] Listening for signal 66 (SIGRTMIN+1). PID: 12174
```

Subscriber 2:
```
denys@ASPZ:~/PWs/ASPZ/12-13 $ ./subscriber 2
[Subscriber] Listening for signal 67 (SIGRTMIN+2). PID: 12198
```

Надішлемо сигнали підписникам

Publisher:
```
denys@ASPZ:~/PWs/ASPZ/12-13 $ ./publisher 12174 1 10
[Publisher] Sent signal 66 (SIGRTMIN+1) with value 10 to PID 12174
denys@ASPZ:~/PWs/ASPZ/12-13 $ ./publisher 12198 2 100
[Publisher] Sent signal 67 (SIGRTMIN+2) with value 100 to PID 12198
```

Результат розсилки:

Subscriber 1:
```
[Subscriber] Signal 66 received from PID 12268 with value 10
```

Subscriber 2:
```
[Subscriber] Signal 67 received from PID 12281 with value 100
```

## Висновок:
В ході виконання практичного заняття 12-13 мною було засвоєно навички надсилання та обробки сигналів, вивчено функції sigaction() та sigqueue().