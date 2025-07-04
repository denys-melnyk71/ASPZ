## Завдання:
Напишіть програму, що імітує лотерею, вибираючи 7 різних цілих чисел у діапазоні від 1 до 49 і ще 6 з 36. Встановіть обмеження на час ЦП (max CPU time) і генеруйте результати вибору чисел (7 із 49, 6 із 36). Обробіть ситуацію, коли ліміт ресурсу вичерпано.

## Звіт:
Максимальний час ЦП встановлюється за допомогою `setrlimit()`  

У разі перевищення ліміту викликається функція `handle_sigxcpu()`. Перевірка перевищення ліміту (та виклик функції у разі його перевищення) відбувається в рядку 
```
signal(SIGXCPU, handle_sigxcpu);
```
де `SIGXCPU` - системний сигнал, який Unix-подібні ОС надсилають процесу, якщо він перевищив встановлене обмеження на час ЦП (CPU time) за допомогою
```
struct rlimit limit = {1, 2};
setrlimit(RLIMIT_CPU, &limit);
```
де `rlimit limit = {soft limit, hard limit}`
- soft limit - це м’яке обмеження, досягнення якого зазвичай не завершує програму одразу, але викликає сигнал SIGXCPU
- hard limit – це жорстке обмеження. Його неможливо перевищити, і якщо програма його досягне, ОС насильно її завершує (kill).

```
Випало 7 з 49: 49 32 37 36 22 29 42 
Випало 6 з 36: 6 31 26 21 12 29 

[!] Час ЦП вичерпано. Програма завершила роботу.
```