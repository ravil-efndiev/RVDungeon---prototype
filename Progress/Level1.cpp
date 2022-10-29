
#include "Level1.h"

Level1::Level1(sf::Shader* coreShader, Player* player, std::vector<Enemy*> &enemies) : Level(player, enemies)
{
    this->coreShader = coreShader;
    this->player = player;

    tileset_t tileset_collisions = GetTileSetFromFile("settings/maps/level1.tls");

    if (tileSet.empty()) tileSet = tileset_collisions.second;
    if (collisionTiles.empty()) collisionTiles = tileset_collisions.first;

    if (charMap.empty()) charMap = GetMapFromFile("settings/maps/level1.tlm");

    map.SetTileSet(tileSet);
    map.SetTileMap(charMap);
    map.SetCollisionTiles(collisionTiles);
    //map.SetMainTileChar('$');
    map.Init();

    this->lightTiles = map.lightTiles;
}

Level1::~Level1() {}

void Level1::Update(const float& deltaTime)
{
    map.UpdateTileCollision(player, deltaTime);

    for (Enemy* enemy : enemies)
        map.UpdateTileCollision(enemy, deltaTime);
}

void Level1::Render(sf::RenderTarget *target)
{
    map.Render(target, coreShader, player->GetCenterPosition());

    for (Enemy *enemy : enemies)
    {   
        if (enemy->GetPosition().y < player->GetPosition().y)
        {
            enemy->Render(target, coreShader);
            player->Render(target, coreShader);
        }
        else if (enemy->GetPosition().y > player->GetPosition().y)
        {
            player->Render(target, coreShader);
            enemy->Render(target, coreShader);
        }
    }

    map.RenderDeffered(target, coreShader, player->GetCenterPosition());
}
