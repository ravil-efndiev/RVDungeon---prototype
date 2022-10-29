
#ifndef UNTITLED7_SWORD_H
#define UNTITLED7_SWORD_H

#include "Weapon.h"
#include "../../Components/AnimationComponent.h"

class Sword : public Weapon
{
private:
    AnimationComponent* pAnimationComponent;
    int damage = 2;

    void InitAnimations();

public:
    Sword();
    Sword(AnimationComponent* pAnimationComponent);
    virtual ~Sword();

    void test() override;
};


#endif //UNTITLED7_SWORD_H
