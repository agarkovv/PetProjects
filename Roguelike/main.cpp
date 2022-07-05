#include <ncurses.h>
#include <memory>
#include <cmath>
#include <vector>
#include "Screen.h"
#include "Frame.h"
#include "ICharacter/ICharacter.h"
#include "Characters/MainCharacter/MainCharacter.h"
#include "Characters/Monster/Monster.h"
#include "Characters/CharacterMaker/ICharacterMaker.h"
#include "Characters/CharacterMaker/MainCharacterMaker.h"
#include "Characters/CharacterMaker/MonsterMaker.h"
#include "ICommand/ICommand.h"
#include "GameLoop/GameLoop.h"

// Функция входа в игру
int main() {

  // Инициализировать ncurses
  Screen screen;

  // Распечатать приветственное сообщение на экране
  screen.add("Welcome to the RR game.\nPress any key to start.\nIf you want to quit press \"q\" or \"Q\"");

  // Подождать, пока пользователь не нажмет клавишу
  int ch = getch();

  // Создать окно ncurses для хранения игровой карты. Это будет в CONST раз больше
  // экрана, и он будет расположен в (0,0) в координатах экрана
  Frame game_map(10 * screen.height(), 10 * screen.width(), 0, 0);

  // Создать подокно ncurses игровой карты. Оно будет иметь размер
  // пользовательского экрана, и он будет изначально расположен в (0, 0)
  Frame viewport(game_map, screen.height(), screen.width(), 0, 0);

  std::unique_ptr<MainCharacterMaker> main_char_maker(new MainCharacterMaker());

  // Инициализировать главного героя. Мы поместим это в середину
  // карты игры (пока)
  std::unique_ptr<MainCharacter> main_char(main_char_maker->MakeCharacter('@', game_map.height() / 2, game_map.width() / 2));

  std::unique_ptr<MonsterMaker> monster_maker(new MonsterMaker());

  // Добавить в игру фиктивного монстра (начнем с жестко заданной позиции монстра).
  // относительно положения главного героя)
  std::vector<std::unique_ptr<Monster>> monster_arr(7);
  monster_arr[0].reset(monster_maker->MakeCharacter('M', main_char->row() + 14, main_char->col() + 14));
  monster_arr[1].reset(monster_maker->MakeCharacter('M', main_char->row() - 20, main_char->col() - 50));
  monster_arr[2].reset(monster_maker->MakeCharacter('M', main_char->row() - 5, main_char->col() - 31));
  monster_arr[3].reset(monster_maker->MakeCharacter('M', main_char->row() + 9, main_char->col() - 33));
  monster_arr[4].reset(monster_maker->MakeCharacter('M', main_char->row() + 19, main_char->col() + 45));
  monster_arr[5].reset(monster_maker->MakeCharacter('M', main_char->row() - 18, main_char->col() + 45));
  monster_arr[6].reset(monster_maker->MakeCharacter('M', main_char->row() + 19, main_char->col() + 45));

  // Генерация карты
  game_map.generate_map();

  // Запустить игровой цикл
  GameLoop game;
  int end_game = game.game_loop(game_map, viewport, *main_char, ch, monster_arr);

  if (end_game == 0) {
    screen.add("YOU WIN! \nEnter any key to exit");
    ch = getch();
  } else if (end_game == 1) {
    screen.add("YOU LOOSE! \nEnter any key to exit");
    ch = getch();
  } else {
    screen.add("SEE YOU SOON! \nEnter any key to exit");
    ch = getch();
  }

  return 0;
}
