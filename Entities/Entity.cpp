
#include "Entity.h"

Entity::Entity()
{
    sprite.setScale(sf::Vector2f(3, 3));
}

Entity::~Entity()
{
    if (movementComponent != NULL ) delete movementComponent;
    if (animationComponent != NULL ) delete animationComponent;
    if (fightComponent != NULL ) delete fightComponent;
    if (hitboxComponent != NULL ) delete hitboxComponent;
}

void Entity::SetPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

sf::Vector2f Entity::GetCenterPosition() const
{
    return sprite.getPosition() + sf::Vector2f
    (
        sprite.getGlobalBounds().width / 2.f,
        sprite.getGlobalBounds().height / 2.f
    );
}

HitboxComponent *Entity::GetHitbox() const
{
    return hitboxComponent;
}

void Entity::StopVelocity(MoveDirections direction)
{
    if (movementComponent)
        movementComponent->StopVelocity(direction);
}

sf::FloatRect Entity::GetBounds() const
{
    return sprite.getGlobalBounds();
}

sf::Vector2f Entity::GetVelocity() const
{
    if (movementComponent)
        return movementComponent->GetVelocity();
}

void Entity::ResetVelocity()
{
    if (movementComponent)
        movementComponent->ResetVelocity();
}

void Entity::Move(float x, float y)
{
    if (movementComponent)
        movementComponent->Move(x, y);
}   

sf::Vector2f Entity::GetPosition() const
{
    return sprite.getPosition();
}

float Entity::GetDistanceBtwEtities(Entity* first, Entity* second, char axis) const
{
    float distance = 0;
    if (axis == 'x')
        distance = abs(first->GetPosition().x - second->GetPosition().x);

    else if (axis == 'y')
        distance = abs(first->GetPosition().y - second->GetPosition().y);


    return distance;
}