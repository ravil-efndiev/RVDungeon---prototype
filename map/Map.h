
#ifndef UNTITLED7_MAP_H
#define UNTITLED7_MAP_H

#include "Tile.h"
#include "../Entities/Enemy.h"

class Map
{
private:
    std::map<char, std::string> tileSet;
    std::list<char> collisionTiles;

    std::vector<std::string> charMap;
    //char mainFloorTile;

    void ParseTileMap(std::vector<std::string> map);
    void GetLightTiles();

public:
    std::vector<Tile*> tiles;
    std::vector<Tile*> lightTiles;
    std::list<char> defferedRenderedTiles;

    Map();
    virtual ~Map();

    void Init();
    void SetTileMap(std::vector<std::string> map);
    void SetTileSet(std::map<char, std::string> tileSet);
    void SetCollisionTiles(std::list<char> collisionTiles);
   // void SetMainTileChar(char tileChar);

    void UpdateTileCollision(Entity* entity, const float& dt);

    void Render(sf::RenderTarget* target, sf::Shader* shader = NULL, const sf::Vector2f playerPos = sf::Vector2f());
    void RenderDeffered(sf::RenderTarget* target, sf::Shader* shader = NULL, const sf::Vector2f playerPos = sf::Vector2f());
};


#endif //UNTITLED7_MAP_H
