
#ifndef UNTITLED7_HITBOXCOMPONENT_H
#define UNTITLED7_HITBOXCOMPONENT_H

#include "../dependencies.h"

class HitboxComponent
{
private:
    enum class HitBoxState
    {
        SPRITE_BASED,
        NO_SPRITE_FLOAT,
        TRIGGER_FLOAT
    };

    HitBoxState state;

    sf::Sprite* sprite;
    sf::RectangleShape hitbox;
    sf::FloatRect nextPosition;

    float offsetX, offsetY;
    sf::Vector2f position;

    void InitHitBox(float width, float height);

public:
    HitboxComponent(sf::Sprite* sprite, float offset_x, float offset_y, float width, float height);
    HitboxComponent(sf::Vector2f position, float width, float height, bool isTrigger = false);
    virtual ~HitboxComponent();

    //Accessors
    const sf::Vector2f& getPosition() const;
    const sf::FloatRect getGlobalBounds() const;
    const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

    //Modifiers
    void setPosition(const sf::Vector2f& position);
    void setPosition(const float x, const float y);

    bool Intersect(sf::FloatRect rect);

    void Update();
    void Render(sf::RenderTarget* target);
};


#endif //UNTITLED7_HITBOXCOMPONENT_H
