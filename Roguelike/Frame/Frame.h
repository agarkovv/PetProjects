#pragma once
#include <ncurses.h>
#include "ICharacter/ICharacter.h"
#define GRASS     ' '
#define EMPTY     '.'
#define WATER     '~'
#define MOUNTAIN  '^'
#define PLAYER    '@'
#define MONSTER   'M'

class Frame {
  // Размеры экрана
  int _height, _width;
  // Позиция экрана
  int _row, _col;
  // Boolean - FALSE для окна и TRUE для подокна (окна просмотра)
  bool _has_super;
  // Указатель на ncurses WINDOW
  WINDOW *_w;
  // Указатель на ncurses WINDOW, это будет NULL для окна и будет указывать на родительское окно
  // для подокна
  WINDOW *_super;
 public:
  // Получить окно
  WINDOW *win();
  // Получить родительское окно
  WINDOW *super();
  // Инициализировать главное окно (без родителя)
  Frame(int nr_rows, int nr_cols, int row_0, int col_0);
  // Инициализировать подокно (окно просмотра) родительским окном
  Frame(Frame &sw, int nr_rows, int nr_cols, int row_0, int col_0);
  ~Frame();
  // Получить тип окна, если TRUE у нас есть подокно, если FALSE у нас есть главное окно
  bool has_super();
  // Получить высоту окна
  int height();
  // Получить ширину окна
  int width();
  // Получить позицию строки (y) окна
  int row();
  // Получить позицию столбца (x) окна
  int col();
  // Обновить окно
  void refresh();
  // Переместить окно в новую позицию (r, c)
  void move(int r, int c);
  // Добавить персонажа в окно
  void add(ICharacter &x);
  // Определить символ «стирание», использовать пустой символ для очистки ячейки или
  // видимый символ для отображения следа игрового персонажа
  void erase(ICharacter &x);
  // Добавить символ в определенной позиции в окно
  void add(ICharacter &x, int row_0, int col_0);
  // Центрировать окно просмотра вокруг персонажа
  void center(ICharacter &x);
  // Создать карту игры
  void generate_map();
  // Проверить, свободна ли позиция
  bool target_position(int row_0, int col_0);
};