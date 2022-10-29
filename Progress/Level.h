
#ifndef UNTITLED7_LEVEL_H
#define UNTITLED7_LEVEL_H

#include "../map/Map.h"
#include "../Entities/Player.h"
#include "../Entities/Enemy.h"

class Level
{
private:

protected:
    typedef std::pair<std::list<char>, std::map<char, std::string>> tileset_t;
    typedef std::vector<std::string> tilemap_t;

    Map map;
    Player* player;
    std::vector<Enemy*> &enemies;

    virtual tilemap_t GetMapFromFile(const char* path);
    virtual tileset_t GetTileSetFromFile(const char* path);
    virtual unsigned int GetNumberOfLines(const char* path);

public: 
    std::vector<Tile*> lightTiles;
    Level(Player* player, std::vector<Enemy*> &enemies);
    virtual ~Level();

    virtual void Update(const float& deltaTime) = 0;
    virtual void Render(sf::RenderTarget* target) = 0;
};


#endif //UNTITLED7_LEVEL_H
