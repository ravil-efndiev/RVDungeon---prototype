
#ifndef UNTITLED7_TILE_H
#define UNTITLED7_TILE_H

#include "../Components/HitboxComponent.h"

class Tile
{
private:
    sf::Vector2u scale;
    sf::Texture texture;
    sf::Vector2i position;

public:
    sf::Sprite sprite;
    std::string texturePath;
    bool hasCollision, interactable = false;
    char setCharacter;
    HitboxComponent* hitboxComponent = NULL;

    Tile(std::string texturePath, sf::Vector2u scale, bool has_collision = false, bool interactable = false);
    virtual ~Tile();

    void DefferedInit();

    void Render(sf::RenderTarget* target, std::vector<sf::Vector2f> lightTiles = std::vector<sf::Vector2f>(), sf::Shader* shader = NULL, sf::Vector2f playerPosition = sf::Vector2f(), const bool showHitbox = false);

    void SetPosition(int x, int y);
    void SetPosition(sf::Vector2i position);
    void SetPositionRaw(sf::Vector2i position);

    void TriggerEnter(sf::FloatRect rect);

    sf::Vector2f GetCenterPosition() const;
    sf::Vector2i GetSimplifiedPosition() const;
};


#endif //UNTITLED7_TILE_H
