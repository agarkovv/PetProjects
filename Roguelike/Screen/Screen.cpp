#include "Screen.h"

// Инициализировать библиотеку ncurses
Screen::Screen() {
  initscr();
  clear();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(0);
  // Получить размеры экрана
  getmaxyx(stdscr, _height, _width);
}

// Очистить ncurses
Screen::~Screen() {
  endwin();
}

// Написать на экране
void Screen::add(const char *message) {
  printw(message);
}

// Получить размеры: высоту
int Screen::height() {
  return _height;
}

// Получить размеры: ширину
int Screen::width() {
  return _width;
}

// Не ждать, пока пользователь нажмет клавишу (неблокирующий ввод-вывод)
void Screen::zerodelay() {
  nodelay(stdscr, TRUE);
}

// Подождать, пока пользователь нажмет клавишу (блокировка ввода-вывода по умолчанию при запуске ncurses)
void Screen::delay() {
  nodelay(stdscr, FALSE);
}