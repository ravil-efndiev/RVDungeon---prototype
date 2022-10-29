
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite *sprite, float offset_x, float offset_y, float width, float height)
    : sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
    hitbox.setPosition(this->sprite->getPosition().x + offset_x, this->sprite->getPosition().y + offset_y);
    InitHitBox(width, height);
    state = HitBoxState::SPRITE_BASED;
}

HitboxComponent::HitboxComponent(sf::Vector2f position, float width, float height, bool isTrigger)
{
    this->position = position; 
    hitbox.setPosition(this->position);
    InitHitBox(width, height);
    if (isTrigger)
        state = HitBoxState::TRIGGER_FLOAT;
    else
        state = HitBoxState::NO_SPRITE_FLOAT;
}

HitboxComponent::~HitboxComponent() {}

//Accessors
const sf::Vector2f & HitboxComponent::getPosition() const
{
    return this->hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
    return this->hitbox.getGlobalBounds();
}

const sf::FloatRect & HitboxComponent::getNextPosition(const sf::Vector2f & velocity)
{
    this->nextPosition.left = this->hitbox.getPosition().x + velocity.x;
    this->nextPosition.top = this->hitbox.getPosition().y + velocity.y;

    return this->nextPosition;
}

//Modifiers
void HitboxComponent::setPosition(const sf::Vector2f& position)
{
    this->hitbox.setPosition(position);
    this->sprite->setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

void HitboxComponent::setPosition(const float x, const float y)
{
    this->hitbox.setPosition(x, y);
    this->sprite->setPosition(x - this->offsetX, y - this->offsetY);
}

void HitboxComponent::Update()
{
    if (state == HitBoxState::SPRITE_BASED)
        hitbox.setPosition(this->sprite->getPosition().x + offsetX, this->sprite->getPosition().y + offsetY);
}

void HitboxComponent::Render(sf::RenderTarget *target)
{
    target->draw(hitbox);
}

bool HitboxComponent::Intersect(sf::FloatRect rect)
{
    return hitbox.getGlobalBounds().intersects(rect);
}

void HitboxComponent::InitHitBox(float width, float height)
{
    hitbox.setSize(sf::Vector2f(width, height));
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineThickness(1.f);
    hitbox.setOutlineColor(sf::Color::Green);
}
