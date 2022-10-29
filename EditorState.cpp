
#include "EditorState.h"

namespace
{
    bool *pSave, *pClose, *pEditorActive;
}

EditorState::EditorState(sf::RenderWindow *window, std::string type, std::stack<State *> *states, sf::View* view)
    : State(window, type, states, view)
{
    unsigned int fieldSizeX, fieldSizeY;
    std::cin >> fieldSizeX >> fieldSizeY;

    std::string str;
    for (int i = 0; i < fieldSizeX; i++)
        str.push_back('.');

    for (int i = 0; i < fieldSizeY; i++)
        emptyMap.push_back(str);

    tileSet.emplace('.', "resources/editor_empty.png");

    InitTileTextures();
    InitTileSet();
    std::cout <<  "lol\n";
    std::cout << tileTextures[0] << tileTextures[1] << tileTextures[2];

    defaultMap.SetTileMap(emptyMap);
    defaultMap.SetTileSet(tileSet);
    defaultMap.Init();

    InitButtonEvents();
}

EditorState::~EditorState() noexcept
{
    for (Tile *tile : tiles)
    {
        delete tile;
    }
    for (gui::Button* btn : buttons)
    {
        delete btn;
    }
}

void EditorState::Update(const float &deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        editorActive = false;

    mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));
    mouseWorldPos = window->mapPixelToCoords(sf::Vector2i(mousePos));

    if (editorActive)
        InputUpdate();

    if (!editorActive)
        for (gui::Button* btn : buttons)
            btn->Update(window);

    if (save) SaveMap();
}

void EditorState::Render(sf::RenderTarget *target)
{
    defaultMap.Render(target);

    if (!editorActive)
        for (gui::Button *btn : buttons)
            btn->Render(target);

    if (editorActive)
        for (Tile* tile : tiles)
            tile->Render(target);
}

void EditorState::InputUpdate()
{
    CameraMove();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        PutTile();
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        DeleteTile();
    }

    #pragma region DONT_OPEN
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) currentTileTexture = tileTextures[0];
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) currentTileTexture = tileTextures[1];
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) currentTileTexture = tileTextures[2];
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) currentTileTexture = tileTextures[3];
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) currentTileTexture = tileTextures[4];
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) currentTileTexture = tileTextures[5];
    #pragma endregion
}

void EditorState::PutTile()
{
    for (int i = 0; i < defaultMap.tiles.size(); i++)
    {
        if (defaultMap.tiles[i]->sprite.getGlobalBounds().contains(mouseWorldPos.x, mouseWorldPos.y))
        {
            for (int j = 0; j < tiles.size(); j++)
            {
                if (tiles[j]->sprite.getPosition() == defaultMap.tiles[i]->sprite.getPosition())
                {
                    delete tiles[j];
                    tiles.erase(tiles.begin() + j);
                }
            }

            Tile* tile = new Tile(currentTileTexture, sf::Vector2u(2, 2));
            tiles.push_back(tile);
            tile->SetPositionRaw(sf::Vector2i(defaultMap.tiles[i]->sprite.getPosition()));
            break;
        }
    }
}

void EditorState::DeleteTile()
{
    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i]->sprite.getGlobalBounds().contains(mouseWorldPos.x, mouseWorldPos.y))
        {
            delete tiles[i];
            tiles.erase(tiles.begin() + i);
            break;
        }
    }
}

void EditorState::SaveMap()
{
    std::vector<std::string> charMap;
    std::string str;
    for (int i = 0; i < emptyMap[0].size(); i++)
        str.push_back('.');

    for (int i = 0; i < emptyMap.size(); i++)
        charMap.push_back(str);

    for (int i = 0; i < defaultMap.tiles.size(); i++)
    {
        for (int j = 0; j < tiles.size(); j++)
        {
            if (defaultMap.tiles[i]->sprite.getPosition() == tiles[j]->sprite.getPosition())
            {
                std::map<char, std::string>::iterator it;
                for (it = tileSet.begin(); it != tileSet.end(); it++)
                {
                    if (it->second == tiles[j]->texturePath)
                    {
                        charMap[tiles[j]->GetSimplifiedPosition().y][tiles[j]->GetSimplifiedPosition().x] = it->first;
                        break;
                    }
                }
            }
        }
    }

    std::ofstream file;
    file.open("settings/maps/level1.tlm");

    for (int i = 0; i < charMap.size(); i++)
    {
        file << charMap[i] << "\n";
    }
    file.close();

    SaveTileSet();

    save = false;
    close = true;
}

void EditorState::SaveTileSet()
{
    std::ofstream file;
    file.open("settings/maps/level1.tls");

    std::map<char, std::string>::iterator it;
    for (it = tileSet.begin(); it != tileSet.end(); it++)
    {
        if (it->first != '.')
            file << it->first << " " << it->second << "\n";
    }
    file.close();
}

void EditorState::InitButtonEvents()
{
    pSave = &save;
    pClose = &close;
    pEditorActive = &editorActive;

    buttons[0]->BindOnClick([]() {
        *pSave = true;
    });
    buttons[1]->BindOnClick([]() {
        *pClose = true;
    });
    buttons[2]->BindOnClick([]() {
        *pEditorActive = true;
    });
}

void EditorState::InitTileTextures()
{
    DIR *dir;
    struct dirent *diread;

    if ((dir = opendir("resources/map/")) != nullptr)
    {
        while ((diread = readdir(dir)) != nullptr)
        {
            tileTextures.push_back("resources/map/" + std::string(diread->d_name));
        }
        closedir (dir);
    }
    else
    {
        std::cerr << "cannot open dir" << std::endl;
    }

    tileTextures.erase(tileTextures.begin(), ++++++tileTextures.begin());
}

void EditorState::InitTileSet()
{
    if (tileTextures.size() <= usableSymbols.size())
    {
        for (int i = 0; i < tileTextures.size(); i++)
        {
            tileSet.emplace(usableSymbols[i], tileTextures[i]);
        }
    }
}

void EditorState::CameraMove()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        view->move(-3, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        view->move(3, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        view->move(0, -3);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        view->move(0, 3);
}
