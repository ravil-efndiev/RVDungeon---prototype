
#include "MainMenuState.h"

namespace
{
    bool* pClose;
    sf::RenderWindow* pWindow;
    std::stack<State*> *pStates;
    sf::View* pView;
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::string type, std::stack<State*> *states, sf::View* view)
        : State(window, type, states, view)
{
    *view = window->getDefaultView();
    BindButtonEvents();
}

MainMenuState::~MainMenuState() noexcept
{
    for (gui::Button* btn : buttons)
    {
        delete btn;
    }
}

void MainMenuState::Update(const float &deltaTime)
{
    CheckForClose();
    for (gui::Button* btn : buttons)
    {
        btn->Update(window);
    }
}

void MainMenuState::Render(sf::RenderTarget *target)
{
    background.Render(target);
    label.Render(target);
    for (gui::Button* btn : buttons) btn->Render(target);
}

void MainMenuState::BindButtonEvents()
{
    pClose = &close;
    pWindow = window;
    pStates = states;
    pView = view;

    buttons[0]->BindOnClick([]() {
        *pClose = true;
    });

    buttons[1]->BindOnClick([]() {
        pWindow->close();
    });

    buttons[2]->BindOnClick([]() {
        pStates->push(new EditorState(pWindow, "editor", pStates, pView));
    });
}
