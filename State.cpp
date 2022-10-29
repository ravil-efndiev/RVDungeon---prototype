
#include "State.h"

State::State(sf::RenderWindow* window, std::string type, std::stack<State*> *states, sf::View* view)
{
    this->window = window;
    this->type = type;
    this->view = view;

    close = false;

    InitTextures();
}

State::~State()
{

}

void State::CheckForClose()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && type == "game")
    {
        close = true;
    }
}

std::string State::GetType()
{
    return type;
}

void State::InitTextures()
{
    textures.emplace("player_sheet", LoadTexture("resources/player_sheet.png"));
    textures.emplace("player_primal", LoadTexture("resources/player_primal.png"));
}

sf::Texture State::LoadTexture(std::string fileName)
{
    sf::Texture texture;
    texture.loadFromFile(fileName);
    return texture;
}

bool State::GetClose()
{
    return close;
}

void State::EndState()
{
    close = true;
}
