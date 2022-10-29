
#include "Tile.h"

Tile::Tile(std::string texturePath, sf::Vector2u scale, bool has_collision, bool interactable)
{
    this->texturePath = texturePath;
    this->hasCollision = has_collision;
    this->interactable = interactable;
    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(scale));
}

Tile::~Tile() 
{
    if (hitboxComponent)
        delete hitboxComponent;
}

void Tile::DefferedInit()
{    
    if (this->interactable)
    {
        sf::Vector2f position = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y);
        hitboxComponent = new HitboxComponent(position, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height, true);
        std::cout << hitboxComponent->getGlobalBounds().width << " " << hitboxComponent->getGlobalBounds().height << std::endl;
        std::cout << hitboxComponent->getPosition().x << " " << hitboxComponent->getPosition().y << std::endl;
    }
}

void Tile::SetPosition(int x, int y)
{
    sprite.setPosition(x * sprite.getGlobalBounds().width, y * sprite.getGlobalBounds().height);
}

void Tile::SetPosition(sf::Vector2i position)
{
    sprite.setPosition(position.x * sprite.getGlobalBounds().width, position.y * sprite.getGlobalBounds().height);
}

void Tile::Render(sf::RenderTarget *target, std::vector<sf::Vector2f> lightTiles, sf::Shader* shader, sf::Vector2f playerPosition, const bool showHitbox)
{
    if (shader)
    {
        std::vector<sf::Vector2f> sources = lightTiles;
        sources.push_back(playerPosition);

        sf::Vector2f actualPositions[2];

        for (int i = 0; i < sources.size(); i++)
        {
            actualPositions[i] = sources[i];
        }

        shader->setUniform("hasTexture", true);
        shader->setUniformArray("lightPos", actualPositions, 2);
        target->draw(sprite, shader);
    }
    else
        target->draw(sprite);
    if (showHitbox && hitboxComponent)
        hitboxComponent->Render(target);
}

void Tile::SetPositionRaw(sf::Vector2i position)
{
    sprite.setPosition(sf::Vector2f(position));
}

sf::Vector2i Tile::GetSimplifiedPosition() const
{
    return sf::Vector2i(sprite.getPosition().x / sprite.getGlobalBounds().width, sprite.getPosition().y / sprite.getGlobalBounds().height);
}

sf::Vector2f Tile::GetCenterPosition() const
{
    return sprite.getPosition() + sf::Vector2f
    (
        sprite.getGlobalBounds().width / 2.f,
        sprite.getGlobalBounds().height / 2.f
    );
}

void Tile::TriggerEnter(sf::FloatRect rect)
{
    if (hitboxComponent->Intersect(rect))
    {
        std::cout << "interact" << std::endl;
    }
}
