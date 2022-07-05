#include "MainCharacterMaker.h"

MainCharacter *MainCharacterMaker::MakeCharacter(char symbol, int row_0, int col_0) {
  return new MainCharacter(symbol, row_0, col_0);
}