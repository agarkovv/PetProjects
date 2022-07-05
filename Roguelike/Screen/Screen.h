#pragma once
#include <ncurses.h>

class Screen {
  int _height, _width;
 public:
  // Инициализировать библиотеку ncurses
  Screen();
  // Очистить ncurses
  ~Screen();
  // Написать на экране
  void add(const char *message);
  // Получить размеры: высоту и ширину соотв.
  int height();
  int width();
  // Не ждать, пока пользователь нажмет клавишу (неблокирующий ввод-вывод)
  void zerodelay();
  // Подождать, пока пользователь нажмет клавишу (блокировка ввода-вывода по умолчанию при запуске ncurses)
  void delay();
};