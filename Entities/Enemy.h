#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include "../AI/FollowAI.h"

class Enemy : public Entity
{
protected:
    sf::Vector2f lightPos;
    std::vector<sf::Vector2f> lightSources;

public:
    Enemy();
    virtual ~Enemy();

    void SetLightSource(sf::Vector2f source);
    void SetLightTiles(std::vector<sf::Vector2f> sources);

    virtual void Update(const float& deltaTime) = 0;
    virtual void Render(sf::RenderTarget* targer, sf::Shader* shader = NULL, const bool showHitbox = false) = 0;
};

#endif
