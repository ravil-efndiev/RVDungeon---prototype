#ifndef BASEAI_H
#define BASEAI_H

#include "../Entities/Entity.h"

class BaseAI
{
protected:
    Entity& target;
    Entity& current;
    
public:
    BaseAI(Entity& target, Entity& current);
    virtual ~BaseAI();

    virtual void Update(const float& deltaTime) = 0;
};

#endif
