#pragma once
#include "../ICharacter/ICharacter.h"
#include "ICharacterMaker.h"
#include "../Monster/Monster.h"

class MonsterMaker : public ICharacterMaker {
 public:
  MonsterMaker() = default;
  Monster *MakeCharacter(char symbol, int row_0, int col_0) override;
};