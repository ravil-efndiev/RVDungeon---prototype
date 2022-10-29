
#include "GameState.h"

GameState::GameState(sf::RenderWindow *window, std::string type, std::stack<State*> *states, sf::View* view)
    : State(window, type, states, view)
{
    player = new Player(textures["player_sheet"], textures["player_primal"]);
    enemies.push_back(new Zombie(textures["player_sheet"], textures["player_primal"], *player));
    enemies.push_back(new Zombie(textures["player_sheet"], textures["player_primal"], *player));

    enemies[1]->SetPosition(0, 600);

    levels.push(new Level1(&coreShader, player, enemies));

    std::vector<sf::Vector2f> tiles;
    for (int i = 0; i < 1; i++)
        tiles.push_back(levels.top()->lightTiles[i]->GetCenterPosition());

    for (Enemy* enemy: enemies) enemy->SetLightTiles(tiles);
    player->InitLightTiles(tiles);
    player->SetPosition(800, 500);
    view->setCenter(player->GetCenterPosition());
    InitShaders();
}

GameState::~GameState() 
{
    delete player;
    for (Enemy* enemy : enemies)
        delete enemy;
    while (!levels.empty())
    {
        delete levels.top();
        levels.pop();
    }
}

void GameState::Update(const float &deltaTime)
{
    CheckForClose();
    
    for (Enemy* enemy : enemies)
    {
        enemy->Update(deltaTime);
        enemy->SetLightSource(player->GetCenterPosition());
    }

    player->Update(deltaTime);
    levels.top()->Update(deltaTime);
    CameraFollow(player, deltaTime);
}

void GameState::Render(sf::RenderTarget *target)
{
    levels.top()->Render(target);
}

void GameState::InitShaders()
{
    coreShader.loadFromFile("resources/shaders/vertex_shader.vert", "resources/shaders/fragment_shader.frag");
}

void GameState::CameraFollow(Entity* entity, const float& deltaTime)
{
    view->move(entity->GetVelocity().x * deltaTime, entity->GetVelocity().y * deltaTime);
}
