## Задание:
### Реализовать Inline vector
- Реализуйте аналог std::vector, но у которого есть еще 1 шаблонный параметр - N. Т.е. до N элементов аллокации в куче не происходит, а если это число превышается, то уже начинается работа с динамической памятью.

Пример - https://github.com/abseil/abseil-cpp/blob/master/absl/container/inlined_vector.h

## Реализация:
- Логика контейнера и непосредственно операции с памятью реализованны в классе _Storage. В этом классе есть массив постоянной длины и динамический массив. При заполнении масива постоянной длины, включается массив переменной. Класс InlineVector - это адаптер, чтобы класс _Storage имел привычные методы, как вектор, а также итератор. Итератор тоже хиттро реализован. Так как имеется два массива, то итератор хранит индекс элемента, а не указатель, а элемент достает через указатель экземпляра класса _Storage.


## Демонстрационная программа:
Сначала вводится число команд. 

> _Команды_:  
> - a - .push_back() ожидается также число
> - b - .pop_back()
> - p - вывод элементов в терминал вектора через итератор
> - i - insert(pos, value), вводится сначала позиция, потом значение
  

## Codestyle
- GNU кодстайл  https://www.gnu.org/prep/standards/standards.html
 
Не надо задумываться о стиле кода. Достаточно написать в терминале команду для автоматического форматирования:
> $ make format

## Сборка:
Для сборки:
> $ make
  
Запустить тесты:
> $ make test
  
Очистить исполняемые и временные файлы:
> $ make clean


./demo - демонстрационная программа.