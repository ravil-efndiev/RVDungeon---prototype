#ifndef FOLLOWAI_H
#define FOLLOWAI_H

#include "BaseAI.h"

class FollowAI : public BaseAI
{
private:
    float GetDistance();
    bool canFollow;

public:
    FollowAI(Entity& target, Entity& current);
    virtual ~FollowAI();

    void Update(const float& deltaTime) override;
};


#endif
