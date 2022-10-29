
#ifndef UNTITLED7_LEVEL1_H
#define UNTITLED7_LEVEL1_H

#include "Level.h"

class Level1 : public Level
{
private:

    std::vector<std::string> charMap;
    std::map<char, std::string> tileSet;
    std::list<char> collisionTiles;

    sf::Shader* coreShader;

public:

    Level1(sf::Shader* coreShader, Player* player, std::vector<Enemy*> &enemies);
    virtual ~Level1();

    void Update(const float& deltaTime) override;
    void Render(sf::RenderTarget* target) override;
};


#endif //UNTITLED7_LEVEL1_H
