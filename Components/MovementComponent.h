
#ifndef RPG_MOVEMENTCOMPONENT_H
#define RPG_MOVEMENTCOMPONENT_H

#include "../dependencies.h"

enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class MovementComponent
{
private:
    float maxVelocity, defaultMaxVelocity;
    float acceleration, deceleration, defaultAcceleration, defaultDeceleration;
    sf::Vector2f velocity;

    sf::Sprite& moveTarget;

    bool notMoveRight, notMoveLeft, notMoveUp, notMoveDown;

public:
    MovementComponent(float maxVelocity, sf::Sprite& moveTarget, float acceleration, float deceleration);
    virtual ~MovementComponent();

    void Update(const float& deltaTime);
    void Move(float x, float y);

    void StopVelocity(MoveDirections direction);
    void ResetVelocity();

    sf::Vector2f GetVelocity() const;

    void EditValues(float maxVelocity, float acceleration, float deceleration);
    void ResetValues();
    bool IsMoving();
};


#endif
