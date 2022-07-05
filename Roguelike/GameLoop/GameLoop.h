#pragma once
#include "../Frame/Frame.h"
#include "../Characters/ICharacter/ICharacter.h"
#include "../Characters/MainCharacter/MainCharacter.h"
#include "../Characters/Monster/Monster.h"
#include <memory>
#include <vector>

class GameLoop {
 public:
  int game_loop(Frame &game_map,
                 Frame &viewport,
                 MainCharacter &main_char,
                 int ch,
                 std::vector<std::unique_ptr<Monster>>& monster_arr);
};

int PredictNextMove(ICharacter& first, ICharacter& second, Frame &game_map, bool is_bullet = false);