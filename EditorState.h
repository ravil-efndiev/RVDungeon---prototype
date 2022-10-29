
#ifndef UNTITLED7_EDITORSTATE_H
#define UNTITLED7_EDITORSTATE_H

#include "State.h"
#include "map/Map.h"

#include "lib/UI/gui.h"

class EditorState : public State
{
private:
    sf::Vector2f mousePos;
    sf::Vector2f mouseWorldPos;

    std::vector<std::string> emptyMap;
    std::vector<Tile*> tiles;
    std::map<char, std::string> tileSet;
    Map defaultMap;

    std::vector<std::string> tileTextures;
    std::string usableSymbols = "#$%@&*+=-!~?<>";

    std::string currentTileTexture;

    std::vector<gui::Button*> buttons =
    {
            new gui::Button(sf::RectangleShape(), "Save", sf::Color::Transparent, sf::Color::Magenta, sf::Vector2f(200, 100), sf::Vector2f(500, 250)),
            new gui::Button(sf::RectangleShape(), "Exit", sf::Color::Transparent, sf::Color::Magenta, sf::Vector2f(200, 100), sf::Vector2f(500, 350)),
            new gui::Button(sf::RectangleShape(), "Continue", sf::Color::Transparent, sf::Color::Magenta, sf::Vector2f(200, 100), sf::Vector2f(500, 450)),
    };

    bool save;
    bool editorActive = true;

    void PutTile();
    void DeleteTile();
    void InputUpdate();

    void SaveMap();
    void SaveTileSet();

    void InitButtonEvents();
    void InitTileTextures();
    void InitTileSet();

    void CameraMove();

public:
    EditorState(sf::RenderWindow* window, std::string type, std::stack<State*> *states, sf::View* view);
    virtual ~EditorState();

    void Update(const float& deltaTime) override;
    void Render(sf::RenderTarget* target) override;
};


#endif //UNTITLED7_EDITORSTATE_H
