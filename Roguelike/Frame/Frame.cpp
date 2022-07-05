#include <ncurses.h>
#include "Frame.h"

// Инициализировать главное окно (без родителя)
Frame::Frame(int nr_rows, int nr_cols, int row_0, int col_0) {
  _has_super = FALSE;
  _super = NULL;
  _w = newwin(nr_rows, nr_cols, row_0, col_0);
  _height = nr_rows;
  _width = nr_cols;
  _row = row_0;
  _col = col_0;
}

// Инициализировать подокно (окно просмотра) родительским окном
Frame::Frame(Frame &sw, int nr_rows, int nr_cols, int row_0, int col_0) {
  _has_super = TRUE;
  _super = sw.win();
  _w = derwin(sw.win(), nr_rows, nr_cols, row_0, col_0);
  _height = nr_rows;
  _width = nr_cols;
  _row = row_0;
  _col = col_0;
}

Frame::~Frame() {
  delwin(_w);
}

// Добавить персонажа в окно
void Frame::add(ICharacter &x) {
  mvwaddch(_w, x.row(), x.col(), x.symbol());
}

// Определить символ «стирание», использовать пустой символ для очистки ячейки или
// видимый символ для отображения следа игрового персонажа
void Frame::erase(ICharacter &x) {
  mvwaddch(_w, x.row(), x.col(), ' ');
}

// Проверить, свободна ли позиция (пока нет карты будет TRUE)
bool Frame::target_position(int row_0, int col_0) {
  // Позиция элемента
  char target = static_cast<char>(mvwinch(_w, row_0, col_0));
  // Если стена - не пускаем
  if (target == '#') {
    return FALSE;
  }
  // Через монстра тоже не пускаем
  if (target == 'M') {
    return FALSE;
  }
  return TRUE;
}

// Добавить символ в определенной позиции в окно
void Frame::add(ICharacter &x, int row_0, int col_0) {
  if ((row_0 >= 0 && row_0 < _height) && (col_0 >= 0 && col_0 < _width)) {
    if (!target_position(row_0, col_0)) return;
    erase(x);
    mvwaddch(_w, row_0, col_0, x.symbol());
    x.pos(row_0, col_0);
  }
}

// Центрировать окно просмотра вокруг персонажа
void Frame::center(ICharacter &x) {
  if (_has_super) {
    int rr = _row, cc = _col, hh, ww;
    int _r = x.row() - _height / 2;
    int _c = x.col() - _width / 2;

    getmaxyx(_super, hh, ww);

    if (_c + _width >= ww) {
      int delta = ww - (_c + _width);
      cc = _c + delta;
    } else {
      cc = _c;
    }

    if (_r + _height >= hh) {
      int delta = hh - (_r + _height);
      rr = _r + delta;
    } else {
      rr = _r;
    }

    if (_r < 0) {
      rr = 0;
    }

    if (_c < 0) {
      cc = 0;
    }

    move(rr, cc);
  }
}

// Обновить окно
void Frame::refresh() {
  if (_has_super) {
    touchwin(_super);
  }
  wrefresh(_w);
}

// Переместить окно в новую позицию (r, c)
void Frame::move(int r, int c) {
  if (_has_super) {
    mvderwin(_w, r, c);
    _row = r;
    _col = c;
    refresh();
  }
}

// Создать карту игры
void Frame::generate_map() {

  int max_x = width() / 2;
  int max_y = height() / 2;

  mvwaddstr(_w, max_y - 15, max_x - 10, "#################");
  mvwaddstr(_w, max_y - 15, max_x + 10, "#############");
  mvwaddstr(_w, max_y - 10, max_x - 10, "#########################");
  mvwaddstr(_w, max_y - 10, max_x + 10, "#################");
  mvwaddstr(_w, max_y - 5, max_x - 20, "#######################");
  mvwaddstr(_w, max_y - 5, max_x + 10, "#######################");
  mvwaddstr(_w, max_y + 5, max_x - 5, "######################################################");
  mvwaddstr(_w, max_y + 10, max_x - 10, "#########################");
  mvwaddstr(_w, max_y + 10, max_x + 30, "#################");
  mvwaddstr(_w, max_y + 15, max_x - 10, "#########################################################");
  mvwaddstr(_w, max_y + 20, max_x - 10, "#################");
  mvwaddstr(_w, max_y + 20, max_x + 5, "##################################");

  for (int y = max_y - 22; y < max_y + 22; ++y) {
    mvwaddch(_w, y, max_x - 78, '#');
  }

  mvwaddstr(_w,
            max_y - 22,
            max_x - 78,
            "###############################################################################"
            "#############################################################################");

  for (int y = max_y - 22; y < max_y + 22; ++y) {
    mvwaddch(_w, y, max_x + 78, '#');
  }

  mvwaddstr(_w,
            max_y + 22,
            max_x - 78,
            "###############################################################################"
            "##############################################################################");

  mvwaddstr(_w, max_y - 13, max_x - 72, "###################################");
  for (int y = max_y - 18; y < max_y - 13; ++y) {
    mvwaddch(_w, y, max_x - 72, '#');
  }

  mvwaddstr(_w, max_y - 18, max_x - 68, "#######################################");
  for (int y = max_y - 18; y < max_y - 14; ++y) {
    mvwaddch(_w, y, max_x - 55, '#');
  }
  for (int y = max_y - 18; y < max_y - 10; ++y) {
    mvwaddch(_w, y, max_x - 30, '#');
  }

  for (int y = max_y - 10; y < max_y - 2; ++y) {
    mvwaddch(_w, y, max_x - 60, '#');
  }
  mvwaddstr(_w, max_y - 2, max_x - 68, "##################################");
  for (int y = max_y - 10; y < max_y - 2; ++y) {
    mvwaddch(_w, y, max_x - 50, '#');
  }
  mvwaddstr(_w, max_y - 7, max_x - 55, "#############################");

  for (int y = max_y + 2; y < max_y + 10; ++y) {
    mvwaddch(_w, y, max_x - 70, '#');
  }
  mvwaddstr(_w, max_y + 10, max_x - 70, "#############################");

  mvwaddstr(_w, max_y + 2, max_x - 55, "#############################");
  for (int y = max_y + 2; y < max_y + 20; ++y) {
    mvwaddch(_w, y, max_x - 55, '#');
  }
  mvwaddstr(_w, max_y + 15, max_x - 68, "#######################################");

  for (int y = max_y + 5; y < max_y + 12; ++y) {
    mvwaddch(_w, y, max_x - 28, '#');
  }
  mvwaddstr(_w, max_y + 7, max_x - 28, "####################");

  for (int y = max_y - 15; y < max_y - 10; ++y) {
    mvwaddch(_w, y, max_x - 10, '#');
  }
  for (int y = max_y + 10; y < max_y + 20; ++y) {
    mvwaddch(_w, y, max_x - 10, '#');
  }
  for (int y = max_y + 10; y < max_y + 20; ++y) {
    mvwaddch(_w, y, max_x - 10, '#');
  }
  for (int y = max_y + 5; y < max_y + 18; ++y) {
    mvwaddch(_w, y, max_x + 30, '#');
  }

  for (int y = max_y - 18; y < max_y - 5; ++y) {
    mvwaddch(_w, y, max_x + 65, '#');
  }

  for (int y = max_y - 3; y < max_y + 8; ++y) {
    mvwaddch(_w, y, max_x + 58, '#');
  }

  for (int y = max_y + 7; y < max_y + 19; ++y) {
    mvwaddch(_w, y, max_x + 70, '#');
  }

  mvwaddstr(_w, max_y - 18, max_x + 52, "#######################");
  mvwaddstr(_w, max_y - 10, max_x + 44, "#########################");
  mvwaddstr(_w, max_y + 5, max_x + 46, "#######################");

  for (int y = max_y - 7; y < max_y + 3; ++y) {
    mvwaddch(_w, y, max_x + 15, '#');
  }
  for (int y = max_y - 7; y < max_y + 6; ++y) {
    mvwaddch(_w, y, max_x + 6, '#');
  }

}

// Получить окно
WINDOW *Frame::win() {
  return _w;
}

// Получить родительское окно
WINDOW *Frame::super() {
  return _super;
}

// Получить тип окна, если TRUE у нас есть подокно, если FALSE у нас есть главное окно
bool Frame::has_super() {
  return _has_super;
}

// Получить высоту окна
int Frame::height() {
  return _height;
}

// Получить ширину окна
int Frame::width() {
  return _width;
}

// Получить позицию строки (y) окна
int Frame::row() {
  return _row;
}

// Получить позицию столбца (x) окна
int Frame::col() {
  return _col;
}