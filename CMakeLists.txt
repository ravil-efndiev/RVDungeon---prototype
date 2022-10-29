cmake_minimum_required(VERSION 3.21)
project(untitled7)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled7 main.cpp Game.cpp Game.h State.cpp State.h MainMenuState.cpp MainMenuState.h GameState.cpp GameState.h lib/UI/Button.cpp lib/UI/Button.h Entities/Player.cpp Entities/Player.h Entities/Entity.cpp Entities/Entity.h Components/MovementComponent.cpp Components/MovementComponent.h Components/AnimationComponent.cpp Components/AnimationComponent.h Components/FightComponent.cpp Components/FightComponent.h dependencies.h lib/UI/gui.h lib/UI/Background.cpp lib/UI/Background.h lib/UI/Label.cpp lib/UI/Label.h map/Tile.cpp map/Tile.h Entities/elements/Weapon.cpp Entities/elements/Weapon.h Entities/elements/Sword.cpp Entities/elements/Sword.h Entities/elements/weapons.h map/Map.cpp map/Map.h EditorState.cpp EditorState.h Progress/Level.cpp Progress/Level.h Progress/Level1.cpp Progress/Level1.h Progress/progress.h Components/HitboxComponent.cpp Components/HitboxComponent.h Entities/Enemy.cpp Entities/Enemy.h Entities/Zombie.cpp Entities/Zombie.h AI/BaseAI.cpp AI/BaseAI.h AI/FollowAI.cpp AI/FollowAI.h)

set(SFML_INCLUDE_DIR "./SFML/include")
set(SFML_LIBRARY_DIR "./SFML/build/lib")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

target_link_libraries (untitled7 sfml-graphics sfml-window sfml-system)
