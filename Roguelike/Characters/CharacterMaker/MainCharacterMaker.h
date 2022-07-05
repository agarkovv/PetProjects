#pragma once
#include "../ICharacter/ICharacter.h"
#include "ICharacterMaker.h"
#include "../MainCharacter/MainCharacter.h"

class MainCharacterMaker : public ICharacterMaker {
 public:
  MainCharacterMaker() = default;
  MainCharacter *MakeCharacter(char symbol, int row_0, int col_0) override;
};