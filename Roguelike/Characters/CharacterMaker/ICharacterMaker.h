#pragma once
#include "../ICharacter/ICharacter.h"

class ICharacterMaker {
 public:
  ICharacterMaker() = default;
  virtual ~ICharacterMaker() = default;
  virtual ICharacter *MakeCharacter(char symbol, int row_0, int col_0) = 0;
};