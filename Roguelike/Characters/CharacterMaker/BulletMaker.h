#pragma once
#include "../ICharacter/ICharacter.h"
#include "ICharacterMaker.h"
#include "../../Bullet/Bullet.h"

class BulletMaker : public ICharacterMaker {
 public:
  Bullet *MakeCharacter(char symbol, int row_0, int col_0) override;
};