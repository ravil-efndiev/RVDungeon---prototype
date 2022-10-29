//
// Created by Belokan on 25.06.22.
//

#ifndef RPG_GAME_H
#define RPG_GAME_H

#include "MainMenuState.h"
#include "GameState.h"
#include <stack>

class Game
{
private:
    sf::RenderWindow* window;

    sf::Event mainEvent;
    sf::Clock dtClock;
    float deltaTime;
    std::stack<State*> states;

    void Update();
    void Render();

    void InitWindow();
    void InitStates();

public:
    sf::View view;

    Game();
    virtual ~Game();

    void Run();
};


#endif //RPG_GAME_H
