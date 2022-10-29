#include "FollowAI.h"

FollowAI::FollowAI(Entity& target, Entity& current) : BaseAI(target, current)
{
}

FollowAI::~FollowAI()
{
}

float FollowAI::GetDistance()
{
    float distance = (abs(
        sqrt(
            ((target.GetPosition().x - current.GetPosition().x) * (target.GetPosition().x - current.GetPosition().x))
            + ((target.GetPosition().y - current.GetPosition().y) * (target.GetPosition().y - current.GetPosition().y))
        )
    ));

    return distance;
}

void FollowAI::Update(const float& deltaTime)
{
    canFollow = GetDistance() <= 300 && GetDistance() >= 50;

    if (canFollow)
    {
        sf::Vector2f moveVec;
        moveVec.x = target.GetPosition().x - current.GetPosition().x;
        moveVec.y = target.GetPosition().y - current.GetPosition().y;

        float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

        moveVec /= vecLength;

        if ((current.GetPosition().x != target.GetPosition().x) && abs(vecLength) < 500.f)
            current.Move(moveVec.x, moveVec.y);
    }
}
