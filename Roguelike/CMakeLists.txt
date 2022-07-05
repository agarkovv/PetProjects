cmake_minimum_required(VERSION 3.0)

project(roguelike)
set(CMAKE_CXX_STANDARD 20)

include_directories(Characters Frame MapGenerator Screen GameLoop ICommand Bullet)

add_executable(roguelike
        main.cpp
        MapGenerator/MapGenerator.cpp
        Frame/Frame.cpp
        Screen/Screen.cpp
        Characters/ICharacter/ICharacter.cpp
        Bullet/Bullet.cpp
        Characters/MainCharacter/MainCharacter.cpp
        Characters/Monster/Monster.cpp
        Characters/CharacterMaker/MainCharacterMaker.cpp
        Characters/CharacterMaker/BulletMaker.cpp
        Characters/CharacterMaker/MonsterMaker.cpp
        ICommand/ICommand.cpp
        GameLoop/GameLoop.cpp
        )

target_link_libraries(${PROJECT_NAME} ncurses)