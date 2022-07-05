#pragma once

class ICharacter {
 public:
  ICharacter() = default;

  // Конструктор персонажа
  ICharacter(char symbol, int row_0, int col_0);

  virtual ~ICharacter() = default;

  // Изменить позицию персонажа
  virtual void pos(int row_0, int col_0);

  // Получить координату по вертикали
  virtual int row();

  // Получить координату по горизонтали
  virtual int col();

  // Получить символ (имя персонажа)
  virtual char symbol();

 protected:
  int _row, _col;
  char _symbol;
};

long long Distance(ICharacter &, ICharacter &);
