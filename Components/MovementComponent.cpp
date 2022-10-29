
#include "MovementComponent.h"

MovementComponent::MovementComponent(float maxVelocity, sf::Sprite& moveTarget,
                                     float acceleration, float deceleration)
                                     : moveTarget(moveTarget)
{
    this->maxVelocity = maxVelocity;
    this->acceleration = acceleration;
    this->deceleration = deceleration;

    defaultMaxVelocity = this->maxVelocity;
    defaultAcceleration = this->acceleration;
    defaultDeceleration = this->deceleration;
}

MovementComponent::~MovementComponent() {}

void MovementComponent::Move(float x, float y)
{
    if ((notMoveRight && x < 0) || (notMoveLeft && x > 0) || (!notMoveRight && !notMoveLeft))
    {
        velocity.x += acceleration * x;
    }
    if ((notMoveUp && y > 0) || (notMoveDown && y < 0) || (!notMoveUp && !notMoveDown))
    {
        velocity.y += acceleration * y;
    }
}

void MovementComponent::Update(const float &deltaTime)
{
    if (velocity.x > 0)
    {
        if (velocity.x > maxVelocity)
            velocity.x = maxVelocity;

        velocity.x -= deceleration;
        if (velocity.x < 0)
            velocity.x = 0;
    }
    else if (velocity.x < 0)
    {
        if (velocity.x < -maxVelocity)
            velocity.x = -maxVelocity;

        velocity.x += deceleration;
        if (velocity.x > 0)
            velocity.x = 0;
    }

    if (velocity.y > 0)
    {
        if (velocity.y > maxVelocity)
            velocity.y = maxVelocity;

        velocity.y -= deceleration;
        if (velocity.y < 0)
            velocity.y = 0;
    }
    else if (velocity.y < 0)
    {
        if (velocity.y < -maxVelocity)
            velocity.y = -maxVelocity;

        velocity.y += deceleration;
        if (velocity.y > 0)
            velocity.y = 0;
    }

    moveTarget.move(GetVelocity() * deltaTime);
}

sf::Vector2f MovementComponent::GetVelocity() const
{
    return velocity;
}

bool MovementComponent::IsMoving()
{
    return velocity.x != 0 || velocity.y != 0;
}

void MovementComponent::EditValues(float maxVelocity, float acceleration, float deceleration)
{
    this->maxVelocity = maxVelocity;
    this->acceleration = acceleration;
    this->deceleration = deceleration;
}

void MovementComponent::ResetValues()
{
    maxVelocity = defaultMaxVelocity;
    acceleration = defaultAcceleration;
    deceleration = defaultDeceleration;
}

void MovementComponent::StopVelocity(MoveDirections direction)
{
    if (direction == MoveDirections::right && velocity.x > 0)
    {
        velocity.x = 0;
        notMoveRight = true;
    }
    else if (direction == MoveDirections::left && velocity.x < 0)
    {
        velocity.x = 0;
        notMoveLeft = true;
    }

    if (direction == MoveDirections::up && velocity.y < 0)
    {
        velocity.y = 0;
        notMoveUp = true;
    }
    else if (direction == MoveDirections::down && velocity.y > 0)
    {
        velocity.y = 0;
        notMoveDown = true;
    }
}

void MovementComponent::ResetVelocity()
{
    notMoveDown = false;
    notMoveRight = false;
    notMoveLeft = false;
    notMoveUp = false;
}
