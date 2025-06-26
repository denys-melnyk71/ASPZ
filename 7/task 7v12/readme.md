## Завдання:
Зробіть систему логування запусків програм, яка не використовує жодного лог-файлу.

## Звіт:
Система логування реалізовано за допомгою функцій openlog, syslog та closelog з заголовку syslog.h. 

Щоб система логування коректно працювала треба було налаштувати syslog.conf. 
В моєму файлі /etc/syslog.conf не було запису
```
user.info                                       /var/log/user.log
```
тому я додав його (використовував редактор ee). Потім я створив відповідний лог-файл і видав собі права читання й запису
```
root@ASPZ:~ # touch /var/log/user.log
root@ASPZ:~ # chmod 644 /var/log/user.log
```

І щоб усе запрацювало перезапустив syslogd
```
root@ASPZ:~ # service syslogd restart
```

### Результат:
```
denys@ASPZ:~/PWs/ASPZ/7/task 7v12 $ ./main
Програма працює...
denys@ASPZ:~/PWs/ASPZ/7/task 7v12 $ grep MyFreeBSDProgram /var/log/user.log
Jun 26 11:47:37 ASPZ MyFreeBSDProgram[5405]: Programm started by user with PID 5405 at 2025-06-26 11:47:37
```
