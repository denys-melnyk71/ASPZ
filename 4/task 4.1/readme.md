## Завдання:
Скільки пам’яті може виділити malloc(3) за один виклик?  

Параметр malloc(3) є цілим числом типу даних size_t, тому логічно максимальне число, яке можна передати як параметр malloc(3), — це максимальне значення size_t на платформі (sizeof(size_t)). У 64-бітній Linux size_t становить 8 байтів, тобто 8 * 8 = 64 біти. Відповідно, максимальний обсяг пам’яті, який може бути виділений за один виклик malloc(3), дорівнює 2^64. Спробуйте запустити код на x86_64 та x86. Чому теоретично максимальний обсяг складає 8 ексабайт, а не 16?


## Звіт:
```
denys@ASPZ:~/PWs/ASPZ/4/task 4.1 $ ./main
Розмір типу size_t: 8 байт
Найбільше значення, яке можна передати malloc: 18446744073709551615
```
malloc(3) може виділити `8 байт` пам’яті.  

Теоретично максимальний обсяг складає 8 ексабайт, а не 16, бо 64-бітному режимі Linux адреси знакові (залежно від реалізації в апаратурі) — тому верхні біти повинні бути однаковими (знакове розширення), щоб уникнути помилок. Це зменшує простір вдвічі 