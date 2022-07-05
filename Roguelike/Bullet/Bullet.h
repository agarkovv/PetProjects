#pragma once
#include "../Characters/ICharacter/ICharacter.h"

class Bullet : public ICharacter {
 public:
  Bullet() = default;
  using ICharacter::ICharacter;
  void SetTarget(int new_idx);
  int GetTarget();
  void SetLifeTime(int new_idx);
  int GetLifeTime();
  const int Range();
  bool CheckLifeTime();
 private:
  int target_monster = -1;
  int lifetime = 20;
};