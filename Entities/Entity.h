
#ifndef RPG_ENTITY_H
#define RPG_ENTITY_H


#include "../Components/MovementComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/FightComponent.h"
#include "../Components/HitboxComponent.h"

class Entity
{
protected:
    MovementComponent* movementComponent = NULL;
    AnimationComponent* animationComponent = NULL;
    FightComponent* fightComponent = NULL;
    HitboxComponent* hitboxComponent = NULL;

    sf::Sprite sprite;
    MoveDirections direction;

    float GetDistanceBtwEtities(Entity* first, Entity* second, char axis) const;

public:
    virtual void Update(const float& deltaTime) = 0;
    virtual void Render(sf::RenderTarget* target, sf::Shader *shader = NULL, const bool showHitbox = false) = 0;

    virtual void SetPosition(float x, float y);
    virtual void Move(float x, float y);

    virtual void ResetVelocity();
    virtual void StopVelocity(MoveDirections dirent);

    virtual sf::Vector2f GetCenterPosition() const;
    virtual sf::Vector2f GetPosition() const;
    
    virtual sf::FloatRect GetBounds() const;
    virtual HitboxComponent* GetHitbox() const;
    virtual sf::Vector2f GetVelocity() const;

    Entity();
    virtual ~Entity();
};


#endif //RPG_ENTITY_H
