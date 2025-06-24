## Ваше завдання – дослідити стек процесу або пригадати, як це робиться. 
Ви можете:
- Автоматично за допомогою утиліти gstack.
- Вручну за допомогою налагоджувача GDB.

Користувачі Ubuntu можуть зіткнутися з проблемою: на момент написання
(Ubuntu 18.04) gstack, схоже, не був доступний (альтернативою може бути
pstack). Якщо gstack не працює, використовуйте другий метод – через
GDB, як показано нижче.  

Спочатку подивіться на стек за допомогою gstack(1). Нижче наведений
приклад стека bash (аргументом команди є PID процесу):
```
$ gstack 14654
#0 0x00007f359ec7ee7a in waitpid () from /lib64/libc.so.6
#1 0x000056474b4b41d9 in waitchild.isra ()
#2 0x000056474b4b595d in wait_for ()
#3 0x000056474b4a5033 in execute_command_internal ()
#4 0x000056474b4a5c22 in execute_command ()
#5 0x000056474b48f252 in reader_loop ()
#6 0x000056474b48dd32 in main ()
$
```
Розбір стека:
- Номер кадру стека відображається ліворуч перед символом #.
- Кадр #0 – це найнижчий кадр. Читайте стек знизу вверх (тобто від
main() – кадр #6 – до waitpid() – кадр #0).
- Якщо процес багатопотоковий, gstack покаже стек кожного потоку
окремо.

### Аналіз стека в режимі користувача через GDB

Щоб переглянути стек процесу вручну, використовуйте GDB,
приєднавшись до процесу.
Нижче наведена невелика тестова програма на C, що виконує кілька
вкладених викликів функцій. Граф викликів виглядає так:
main() --&gt; foo() --&gt; bar() --&gt; bar_is_now_closed() --&gt; pause()
Системний виклик pause() – це приклад блокуючого виклику. Він
переводить викликаючий процес у сплячий режим, очікуючи (або
блокуючи) сигнал. У цьому випадку процес блокується, поки не отримає
будь-який сигнал.
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MSG "In function %20s; &localvar = %p\n"

static void bar_is_now_closed(void) {
    int localvar = 5;
    printf(MSG, __FUNCTION__, &localvar);
    printf("\n Now blocking on pause()...\n");
    pause();
}

static void bar(void) {
    int localvar = 5;
    printf(MSG, __FUNCTION__, &localvar);
    bar_is_now_closed();
}

static void foo(void) {
    int localvar = 5;
    printf(MSG, __FUNCTION__, &localvar);
    bar();
}

int main(int argc, char **argv) {
    int localvar = 5;
    printf(MSG, __FUNCTION__, &localvar);
    foo();
    exit(EXIT_SUCCESS);
}
```
Тепер відкрийте GDB
У ньому підключіться (attach) до процесу (в наведеному прикладі PID =
24957) і дослідіть стек за допомогою команди backtrace (bt):
```
$ gdb --quiet
(gdb) attach 24957
Attaching to process 24957
Reading symbols from &lt;...&gt;/hspl/unit2/stacker...done.
Reading symbols from /lib64/libc.so.6...Reading symbols from
/usr/lib/debug/usr/lib64/libc-2.26.so.debug...done.
done.
Reading symbols from /lib64/ld-linux-x86-64.so.2...Reading symbols
...
(gdb) bt
...
```
__Примітка__: В Ubuntu, через питання безпеки, GDB не дозволяє
підключатися до довільного процесу. Це можна обійти, запустивши GDB
від імені користувача root.
## Звіт
gstack недоступний
```
denys@ASPZ:~/PWs $ gstack 14654
/bin/sh: gstack: not found
```
Тому перегляну стек процесу вручну, використовуйте GDB. 
Спочатку треба скомпілювати код в режимі відладки.
```
denys@ASPZ:~/PWs/ASPZ/2/task4 $ gcc -g main.c -o main
```
Потім запустити його в фоновому режимі
```
denys@ASPZ:~/PWs/ASPZ/2/task4 $ ./main &
denys@ASPZ:~/PWs/ASPZ/2/task4 $ In function                 main; &localvar = 0x820c9445c
In function                  foo; &localvar = 0x820c9442c
In function                  bar; &localvar = 0x820c9440c
In function    bar_is_now_closed; &localvar = 0x820c943ec

 Now blocking on pause()...
```
і дізнатись його PID
```
ps aux | grep main
denys      1565   0.0  0.0      13728   1768  0  I    09:24     0:00.00 ./main
denys      1577   0.0  0.0        512    328  0  R+   09:24     0:00.00 grep main
denys@ASPZ:~/PWs/ASPZ/2/task4 $ 
```
В результаті маємо PID = `1565`. Тепер можна переглянути стек процесу:
```
root@ASPZ:~ # gdb --quiet
(gdb) attach 1565
Attaching to process 1565
Reading symbols from /home/denys/PWs/ASPZ/2/task4/main...
Reading symbols from /lib/libc.so.7...
Reading symbols from /usr/lib/debug//lib/libc.so.7.debug...
Reading symbols from /libexec/ld-elf.so.1...
Reading symbols from /usr/lib/debug//libexec/ld-elf.so.1.debug...
_sigsuspend () at _sigsuspend.S:4
warning: 4      _sigsuspend.S: No such file or directory
(gdb) bt
#0  _sigsuspend () at _sigsuspend.S:4
#1  0x0000000821e61c35 in __pause () at /usr/src/lib/libc/gen/pause.c:51
#2  0x000000000040068b in bar_is_now_closed () at main.c:12
#3  0x00000000004006bd in bar () at main.c:18
#4  0x00000000004006ef in foo () at main.c:24
#5  0x0000000000400728 in main (argc=1, argv=0x820c944e8) at main.c:30
```
