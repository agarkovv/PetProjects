#include "BulletMaker.h"

Bullet *BulletMaker::MakeCharacter(char symbol, int row_0, int col_0) {
  return new Bullet(symbol, row_0, col_0);
}