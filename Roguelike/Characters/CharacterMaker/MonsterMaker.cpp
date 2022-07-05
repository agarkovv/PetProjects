#include "MonsterMaker.h"
#include "../ICharacter/ICharacter.h"
#include "ICharacterMaker.h"
#include "../Monster/Monster.h"

Monster *MonsterMaker::MakeCharacter(char symbol, int row_0, int col_0) {
  return new Monster(symbol, row_0, col_0);
}