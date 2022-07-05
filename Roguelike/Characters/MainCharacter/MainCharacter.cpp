#include "MainCharacter.h"

int MainCharacter::GetBullets() const {
  return bullets;
}

void MainCharacter::SetBullets(int new_bullets) {
  bullets = new_bullets;
}