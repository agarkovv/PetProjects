#include "Bullet.h"

void Bullet::SetTarget(int new_idx) {
  target_monster = new_idx;
}

int Bullet::GetTarget() {
  return target_monster;
}

void Bullet::SetLifeTime(int new_idx) {
  lifetime = new_idx;
}

int Bullet::GetLifeTime() {
  return lifetime;
}

const int Bullet::Range() {
  return 100;
}

bool Bullet::CheckLifeTime() {
  return GetLifeTime() == 0;
}