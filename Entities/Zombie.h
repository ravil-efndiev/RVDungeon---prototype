#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Enemy.h"

class Zombie : public Enemy
{
private:

    Entity& player;
    FollowAI* followAi;

    void InitComponents(sf::Texture& textureSheet);
    void GenerateAnimations();

    void AnimateByDirection(std::string walkAnim, std::string idleAnim, const float& deltaTime);
    void UpdateDirections();

public:
    Zombie(sf::Texture& textureSheet, sf::Texture& primalTexture, Player& player);
    virtual ~Zombie();

    void Update(const float& deltaTime) override;
    void Render(sf::RenderTarget* targer, sf::Shader* shader = NULL, const bool showHitbox = false) override;
};

#endif
