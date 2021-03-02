#pragma once

struct IntArray {
  int *data;
  int size;
};

/** Создаёт динамический массив размера size и сохраняет его
 *  в поле data переменной arr. Поле size структуры arr становится
 *  равным параметру size */
void create(IntArray* arr, int size);
void create(IntArray& arr, int size);

/** Возвращает элемент массива с индексом index, при этом проверяет
 *  выход за границы массива. Если index лежит за пределами массива,
 *  вывести сообщение об ошибке и прервать работу программы */
int get(IntArray* arr, int index);
int get(IntArray& arr, int index);

/** Изменяет значение элемента массива с индексом index на значение
 *  параметра value, при этом проверяет выход за границы массива.
 *  Если index лежит за пределами массива, вывести сообщение об ошибке
 *  и прервать работу программы */
void set(IntArray* arr, int index, int value);
void set(IntArray& arr, int index, int value);

/** Выводит на экран содержимое массива в формате: [1, 2, 3] */
void print(IntArray* arr);
void print(IntArray& arr);

/** Изменяет размер массива с сохранением элементов. Если новый размер меньше,
 *  хвостовые элементы обрезаются, если больше, то дополнительные элементы
 *  инициализируются нулём */
void resize(IntArray* arr, int newSize);
void resize(IntArray& arr, int newSize);

/** Освобождает память занятую массивом. Поле data становится равным nullptr,
 *  поле size становится равным нулю. Предусмотреть случай попытки удаления
 *  уже удалённого массива */
void destroy(IntArray* arr);
void destroy(IntArray& arr);
