#pragma once
#include "../Frame/Frame.h"
#include "../Characters/ICharacter/ICharacter.h"

class ICommand {
 public:

  ICommand(ICharacter &character);

  virtual void execute(Frame &game_map, Frame &viewpoint) const = 0;

  ICharacter &character;
};

class KeyLeft : public ICommand {
 public:
  KeyLeft(ICharacter &character) : ICommand(character) {}

  void execute(Frame &game_map, Frame &viewpoint) const override;
};

class KeyRight : public ICommand {
 public:
  KeyRight(ICharacter &character) : ICommand(character) {}

  void execute(Frame &game_map, Frame &viewpoint) const override;
};

class KeyUp : public ICommand {
 public:
  KeyUp(ICharacter &character) : ICommand(character) {}

  void execute(Frame &game_map, Frame &viewpoint) const override;
};

class KeyDown : public ICommand {
 public:
  KeyDown(ICharacter &character) : ICommand(character) {}

  void execute(Frame &game_map, Frame &viewpoint) const override;
};
