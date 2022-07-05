#include "GameLoop.h"
#include "../ICommand/ICommand.h"
#include <cmath>
#include "../Bullet/Bullet.h"
#include "../Characters/CharacterMaker/BulletMaker.h"
#include "../Characters/MainCharacter/MainCharacter.h"
#include "../Characters/ICharacter/ICharacter.h"
#include "../Characters/Monster/Monster.h"
#include <vector>

int GameLoop::game_loop(Frame &game_map,
                         Frame &viewport,
                         MainCharacter &main_char,
                         int ch,
                         std::vector<std::unique_ptr<Monster>>& monster_arr) {
  // Проверка на выход из игры по горячей клавише
  if (ch == 'q' || ch == 'Q') return 2;

  // Добавляем монстра в игру
  for (size_t i = 0; i < monster_arr.size(); ++i) {
    game_map.add(*monster_arr[i]);
  }

  // Добавляем ГГ в игру
  game_map.add(main_char);
  viewport.center(main_char);
  viewport.refresh();

  std::vector<std::unique_ptr<Bullet>> bullet_vector;

  while (1) {

    ch = getch();

    // Движения ГГ
    if (ch == KEY_LEFT) {
      KeyLeft left_command(main_char);
      left_command.execute(game_map, viewport);
      viewport.center(main_char);

    } else if (ch == KEY_RIGHT) {
      KeyRight right_command(main_char);
      right_command.execute(game_map, viewport);
      viewport.center(main_char);

    } else if (ch == KEY_UP) {
      KeyUp up_command(main_char);
      up_command.execute(game_map, viewport);
      viewport.center(main_char);

    } else if (ch == KEY_DOWN) {
      KeyDown down_command(main_char);
      down_command.execute(game_map, viewport);
      viewport.center(main_char);

    } else if (ch == 'f' || ch == 'F') {
      // Создаем объект пули, если есть патроны
      // Уменьшаем количество патронов на 1
      if (main_char.GetBullets() > 0) {
        std::unique_ptr<BulletMaker> maker(new BulletMaker());
        bullet_vector.push_back(std::unique_ptr<Bullet>(maker->MakeCharacter('*', main_char.row(), main_char.col())));
        main_char.SetBullets(main_char.GetBullets() - 1);
      }

    } else if (ch == 'q' || ch == 'Q') {
      return 2;
    }

    for (size_t i = 0; i < bullet_vector.size(); ++i) {
      long long min_dist = std::numeric_limits<long long>::max();
      int nearest_monster = -1;
      for (int j = 0; j < monster_arr.size(); ++j) {
        long long cur_dist = Distance(*bullet_vector[i], *monster_arr[j]);
        if (cur_dist < min_dist) {
          min_dist = cur_dist;
          nearest_monster = j;
        }
      }
      if (monster_arr.empty()) {
        break;
      }
      bullet_vector[i]->SetTarget(nearest_monster);

      int pos = PredictNextMove(*bullet_vector[i], *monster_arr[bullet_vector[i]->GetTarget()], game_map, true);

      switch (pos) {
        case 0: {
          KeyLeft left_command(*(bullet_vector[i]));
          left_command.execute(game_map, viewport);
          break;
        }
        case 1: {
          KeyRight right_command(*(bullet_vector[i]));
          right_command.execute(game_map, viewport);
          break;
        }
        case 2: {
          KeyUp up_command(*(bullet_vector[i]));
          up_command.execute(game_map, viewport);
          break;
        }
        case 3: {
          KeyDown down_command(*(bullet_vector[i]));
          down_command.execute(game_map, viewport);
          break;
        }
      }

      if (monster_arr.empty()) {
        break;
      }

      bullet_vector[i]->SetLifeTime(bullet_vector[i]->GetLifeTime() - 1);
      if (bullet_vector[i]->CheckLifeTime()) {
        game_map.erase(*bullet_vector[i]);
        bullet_vector.erase(bullet_vector.begin() + i);
      } else {
        if (Distance(*bullet_vector[i], *monster_arr[bullet_vector[i]->GetTarget()]) < 2) {
          monster_arr[bullet_vector[i]->GetTarget()]->SetHP(monster_arr[bullet_vector[i]->GetTarget()]->GetHP() - 1);
          if (monster_arr[bullet_vector[i]->GetTarget()]->CheckHP()) {
            game_map.erase(*monster_arr[bullet_vector[i]->GetTarget()]);
            monster_arr.erase(monster_arr.begin() + bullet_vector[i]->GetTarget());
            main_char.SetBullets(main_char.GetBullets() + 5);
          }
          game_map.erase(*bullet_vector[i]);
          bullet_vector.erase(bullet_vector.begin() + i);
        }
      }
    }

    // Считаем расстояние до монстров, чтобы те начали двигаться, когда ГГ попадет в радиус их видимости
    // Влево
    for (int i = 0; i < monster_arr.size(); ++i) {
      int pos = PredictNextMove(*monster_arr[i], main_char, game_map);

      switch (pos) {
        case 0: {
          KeyLeft left_command(*(monster_arr[i]));
          left_command.execute(game_map, viewport);
          break;
        }
        case 1: {
          KeyRight right_command(*(monster_arr[i]));
          right_command.execute(game_map, viewport);
          break;
        }
        case 2: {
          KeyUp up_command(*(monster_arr[i]));
          up_command.execute(game_map, viewport);
          break;
        }
        case 3: {
          KeyDown down_command(*(monster_arr[i]));
          down_command.execute(game_map, viewport);
          break;
        }
      }
    }
    viewport.center(main_char);
    viewport.refresh();

    if (monster_arr.empty()) {
      break;
    }
  }
  return 0;
}

int PredictNextMove(ICharacter& first, ICharacter& second, Frame &game_map, bool is_bullet) {
  int pos = -1, score = game_map.height() * game_map.height() + game_map.width() * game_map.width(), dist = -1;
  if (game_map.target_position(first.row(), first.col() - 1)) {
    dist = std::pow(second.row() - first.row(), 2)
        + std::pow(second.col() - (first.col() - 1), 2);
    if (score > dist && dist < 30 + 500 * is_bullet) {
      score = dist;
      pos = 0;
    }
  }
  // Вправо
  if (game_map.target_position(first.row(), first.col() + 1)) {
    dist = std::pow(second.row() - first.row(), 2)
        + std::pow(second.col() - (first.col() + 1), 2);
    if (score > dist && dist < 30 + 500 * is_bullet) {
      score = dist;
      pos = 1;
    }
  }
  // Вверх
  if (game_map.target_position(first.row() - 1, first.col())) {
    dist = std::pow(second.row() - (first.row() - 1), 2)
        + std::pow(second.col() - first.col(), 2);
    if (score > dist && dist < 30 + 500 * is_bullet) {
      score = dist;
      pos = 2;
    }
  }
  // Вниз
  if (game_map.target_position(first.row() + 1, first.col())) {
    dist = std::pow(second.row() - (first.row() + 1), 2)
        + std::pow(second.col() - first.col(), 2);
    if (score > dist && dist < 30 + 500 * is_bullet) {
      score = dist;
      pos = 3;
    }
  }
  return pos;
}