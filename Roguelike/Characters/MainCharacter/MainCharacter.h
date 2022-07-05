#pragma once
#include "../ICharacter/ICharacter.h"

class MainCharacter : public ICharacter {
 public:
  MainCharacter() = default;
  using ICharacter::ICharacter;
  int GetBullets() const;
  void SetBullets(int new_bullets);
 private:
  //По дефолту сделаем 10 пуль
  int bullets = 10;
};