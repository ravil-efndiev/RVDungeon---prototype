
#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
    for (Tile *tile : tiles)
    {
        delete tile;
    }
}

void Map::Init()
{
    ParseTileMap(charMap);
    for (Tile* tile : tiles)
    {
        if (tile->texturePath == "resources/map/chest_1.png")
        {
            tile->interactable = true;
            tile->DefferedInit();
        }
    }
}

void Map::Render(sf::RenderTarget *target, sf::Shader* shader, const sf::Vector2f playerPos)
{
    std::vector<sf::Vector2f> lightTilesPositions;

    for (int i = 0; i < lightTiles.size(); i++)
    {
        lightTilesPositions.push_back(lightTiles[i]->GetCenterPosition());
    }

    for (Tile *tile : tiles)
    {
        if (!std::count(defferedRenderedTiles.begin(), defferedRenderedTiles.end(), tile->setCharacter))
            tile->Render(target, lightTilesPositions, shader, playerPos);
    }
}

void Map::RenderDeffered(sf::RenderTarget *target, sf::Shader* shader, const sf::Vector2f playerPos)
{
    std::vector<sf::Vector2f> lightTilesPositions;

    for (int i = 0; i < lightTiles.size(); i++)
    {
        lightTilesPositions.push_back(lightTiles[i]->GetCenterPosition());
    }

    for (Tile *tile : tiles)
    {
        if (std::count(defferedRenderedTiles.begin(), defferedRenderedTiles.end(), tile->setCharacter))
            tile->Render(target, lightTilesPositions, shader, playerPos);
    }
}

void Map::ParseTileMap(std::vector<std::string> map)
{
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            Tile* tile = NULL;
            bool hasLight = false;
            bool isDeffered = false;
            std::string path = tileSet[map[i][j]];
            if (path.find("resources/map/[LIGHT]") != std::string::npos)
            {
                //defferedRenderedTiles.push_back(map[i][j]);
                hasLight = true;
                //isDeffered = true;
            }

            bool hasCollision = false;
            std::list<char>::iterator it;
            for (it = collisionTiles.begin(); it != collisionTiles.end(); it++)
            {
                if (map[i][j] == *it)
                {
                    hasCollision = true;
                    break;
                }
            }
            Tile* tileBcg = NULL;

            if (hasCollision && !isDeffered)
                tile = new Tile(tileSet[map[i][j]], sf::Vector2u(2, 2), true);
            else if (!hasCollision && !isDeffered)
                tile = new Tile(tileSet[map[i][j]], sf::Vector2u(2, 2));
            else if (isDeffered)
            {
                tile = new Tile(tileSet[map[i][j]], sf::Vector2u(2, 2));
                tileBcg = new Tile(tileSet['$'], sf::Vector2u(2, 2));
            }
            
            tile->setCharacter = map[i][j];

            if (hasLight) lightTiles.push_back(tile);

            if (tileBcg != NULL)
            {
                tiles.push_back(tile);
                tiles.push_back(tileBcg);
                tile->SetPosition(j, i);
                tileBcg->SetPosition(i, j);
            }
            else
            {
                tiles.push_back(tile);
                tile->SetPosition(j, i);
            }
        }
    }
}

void Map::UpdateTileCollision(Entity *entity, const float &dt)
{
    int collisions = 0;

    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i]->hasCollision)
        {
            if (tiles[i]->interactable)
            {
                tiles[i]->TriggerEnter(entity->GetBounds());
            }
            if (entity->GetHitbox()->Intersect(tiles[i]->sprite.getGlobalBounds()))
            {
                collisions++;
                sf::FloatRect entityBounds = entity->GetBounds();
                sf::FloatRect wallBounds = tiles[i]->sprite.getGlobalBounds();

                //Bottom collision
                if (entityBounds.top < wallBounds.top
                        && entityBounds.top + entityBounds.height < wallBounds.top + wallBounds.height
                        && entityBounds.left < wallBounds.left + wallBounds.width
                        && entityBounds.left + entityBounds.width > wallBounds.left
                    )
                {
                    entity->StopVelocity(MoveDirections::down);
                }

                //Top collision
                else if (entityBounds.top > wallBounds.top
                         && entityBounds.top + entityBounds.height > wallBounds.top + wallBounds.height
                         && entityBounds.left < wallBounds.left + wallBounds.width
                         && entityBounds.left + entityBounds.width > wallBounds.left
                    )
                {
                    entity->StopVelocity(MoveDirections::up);
                }

                //Right collision
                else if (entityBounds.left < wallBounds.left
                        && entityBounds.left + entityBounds.width < wallBounds.left + wallBounds.width
                        && entityBounds.top < wallBounds.top + wallBounds.height
                        && entityBounds.top + entityBounds.height > wallBounds.top
                    )
                {
                    entity->StopVelocity(MoveDirections::right);
                }

                //Left collision
                else if (entityBounds.left > wallBounds.left
                         && entityBounds.left + entityBounds.width > wallBounds.left + wallBounds.width
                         && entityBounds.top < wallBounds.top + wallBounds.height
                         && entityBounds.top + entityBounds.height > wallBounds.top
                        )
                {
                    entity->StopVelocity(MoveDirections::left);
                }
            }
        }
    }
    if (collisions == 0)
        entity->ResetVelocity();
}

void Map::SetCollisionTiles(std::list<char> collisionTiles)
{
    this->collisionTiles = collisionTiles;
}

void Map::SetTileMap(std::vector<std::string> map)
{
    charMap = map;
}

void Map::SetTileSet(std::map<char, std::string> tileSet)
{
    this->tileSet = tileSet;
}
