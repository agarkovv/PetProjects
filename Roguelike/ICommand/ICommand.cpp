#include "ICommand.h"

ICommand::ICommand(ICharacter &character) : character(character) {}

void KeyLeft::execute(Frame &game_map, Frame &viewpoint) const {
  game_map.add(character, character.row(), character.col() - 1);
  viewpoint.refresh();
}

void KeyRight::execute(Frame &game_map, Frame &viewpoint) const {
  game_map.add(character, character.row(), character.col() + 1);
  viewpoint.refresh();
}

void KeyUp::execute(Frame &game_map, Frame &viewpoint) const {
  game_map.add(character, character.row() - 1, character.col());
  viewpoint.refresh();
}

void KeyDown::execute(Frame &game_map, Frame &viewpoint) const {
  game_map.add(character, character.row() + 1, character.col());
  viewpoint.refresh();
}
