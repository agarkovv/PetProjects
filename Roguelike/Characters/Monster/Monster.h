#pragma once
#include "../ICharacter/ICharacter.h"

class Monster : public ICharacter {
 public:
  Monster() = default;
  using ICharacter::ICharacter;
  const int Range();
  int GetHP();
  void SetHP(int new_hp);
  bool CheckHP();
 private:
  int hp = 4;
};