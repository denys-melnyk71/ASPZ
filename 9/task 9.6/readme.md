## Завдання:
Напишіть програму, яка виконує команду ls -l, щоб переглянути власника і права доступу до файлів у своєму домашньому каталозі, в /usr/bin та в /etc.
 Продемонструйте, як ваша програма намагається обійти різні власники та права доступу користувачів, а також здійснює спроби читання, запису та виконання цих файлів.

## Звіт:
Для перевірки права доступу користувачів в програмі, було прийнято рішення, використовувати функцію access() з заголовку unistd.h

У більшості Unix/Linux-систем шлях до домашнього каталогу користувача зберігається в змінній середовища HOME, тож для знаходження домашнього каталогу використовується getenv("HOME"). Тут функція getenv() використовується для доступу до змінних середовища.

Загалом, всі інші аспекти реалізовані аналогічно до попередніх завдань.