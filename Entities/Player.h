
#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H

#include "Entity.h"

class Player : public Entity
{
private:
    bool inFight;
    std::map<std::string, Weapon*> ownedWeapons;
    Weapon* currentWeapon;
    float lightRadius = 3.0f;

    void InitComponents(sf::Texture& textureSheet);
    void GenerateAnimations();

    void UpdateInput(const float& deltaTime);
    void AnimateByDirection(std::string walkAnim, std::string runAnim, std::string idleAnim, const float& deltaTime);

public:
    std::vector<sf::Vector2f> lightTiles;

    Player();
    Player(sf::Texture& textureSheet, sf::Texture& primalTexture);
    virtual ~Player();

    void InitLightTiles(std::vector<sf::Vector2f> lightTiles);

    void Update(const float& deltaTime) override;
    void Render(sf::RenderTarget* target, sf::Shader *shader = NULL, const bool showHitbox = false) override;
};


#endif
