#include "ICharacter.h"
#include "../../Frame/Frame.h"

// Конструктор персонажа
ICharacter::ICharacter(char symbol, int row_0, int col_0) {
  _symbol = symbol;
  _row = row_0;
  _col = col_0;
}

// Изменить позицию персонажа
void ICharacter::pos(int row_0, int col_0) {
  _row = row_0;
  _col = col_0;
}

// Получить координату по вертикали
int ICharacter::row() {
  return _row;
}

// Получить координату по горизонтали
int ICharacter::col() {
  return _col;
}

// Получить символ (имя персонажа)
char ICharacter::symbol() {
  return _symbol;
}

long long Distance(ICharacter& first, ICharacter& second) {
  return (first.col() - second.col()) * (first.col() - second.col()) +
         (first.row() - second.row()) * (first.row() - second.row());
}