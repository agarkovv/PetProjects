#include "Monster.h"

const int Monster::Range() {
  return 20;
}

int Monster::GetHP() {
  return hp;
}

void Monster::SetHP(int new_hp) {
  hp = new_hp;
}

bool Monster::CheckHP() {
  return hp == 0;
}