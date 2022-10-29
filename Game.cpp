
#include "Game.h"

Game::Game() {}

Game::~Game()
{
    delete window;

    while (!states.empty())
    {
        delete states.top();
        states.pop();
    }
}

// main methods
void Game::Run()
{
    InitWindow();
    InitStates();

    while (window->isOpen())
    {
        Update();
        Render();
    }
}

void Game::Update()
{
    while (window->pollEvent(mainEvent))
    {
        if (mainEvent.type == sf::Event::Closed)
        {
            window->close();
        }
    }

    deltaTime = dtClock.restart().asSeconds();
    //std::cout << 1.f / (deltaTime) << std::endl;

    if (!states.empty())
    {
        states.top()->Update(deltaTime);
        
        if (states.top()->close)
        {
            std::string type = states.top()->GetType();

            delete states.top();
            states.pop();

            if (type == "game" || type == "editor")
                states.push(new MainMenuState(window, "menu", &states, &view));
            else if (type == "menu")
                states.push(new GameState(window, "game", &states, &view));
        }
    }
}

void Game::Render()
{
    window->clear();
    window->setView(view);

    if (!states.empty())
         states.top()->Render(window);

    window->display();
}

// init methods
void Game::InitWindow()
{
    window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Rpg");
    window->setFramerateLimit(60);

    view = window->getDefaultView();
}

void Game::InitStates()
{
    states.push(new MainMenuState(window, "menu", &states, &view));
}
