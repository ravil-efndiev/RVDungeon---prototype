
#ifndef RPG_MAINMENUSTATE_H
#define RPG_MAINMENUSTATE_H

#include "State.h"
#include "EditorState.h"
#include "GameState.h"

#include "lib/UI/gui.h"

class MainMenuState : public State
{
private:
    gui::Background background = gui::Background(sf::Color( 53, 58, 77), window);
    gui::Label label = gui::Label("Game Ravakus", sf::Color::Black, sf::Vector2f(2.5f, 2.5f), sf::Vector2f(50, 20), "resources/Roboto-Regular.ttf");

    std::vector<gui::Button*> buttons =
    {
        new gui::Button(sf::RectangleShape(), "Play",  sf::Color::Transparent, sf::Color::Black, sf::Vector2f(200, 100), sf::Vector2f(50, 170)),
        new gui::Button(sf::RectangleShape(), "Exit",  sf::Color::Transparent, sf::Color::Black, sf::Vector2f(200, 100), sf::Vector2f(50, 320)),
        new gui::Button(sf::RectangleShape(), "Editor",  sf::Color::Transparent, sf::Color::Black, sf::Vector2f(200, 100), sf::Vector2f(50, 470)),
    };

    void BindButtonEvents();

public:
    MainMenuState(sf::RenderWindow* window, std::string type, std::stack<State*> *states, sf::View* view);
    virtual ~MainMenuState();

    void Update(const float& deltaTime) override;
    void Render(sf::RenderTarget* target) override;
};


#endif //RPG_MAINMENUSTATE_H
