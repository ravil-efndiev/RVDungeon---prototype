
#include "Sword.h"

Sword::Sword(AnimationComponent *pAnimationComponent) : Weapon(damage)
{
    this->pAnimationComponent = pAnimationComponent;
    InitAnimations();
}

Sword::~Sword() noexcept {}

void Sword::InitAnimations()
{
    std::string right0 = "SWORD_ATTACK_RIGHT_0";
    std::string right1 = "SWORD_ATTACK_RIGHT_1";
    std::string left0 = "SWORD_ATTACK_LEFT_0";
    std::string left1 = "SWORD_ATTACK_LEFT_1";

    pAnimationComponent->AddAnimation(right0, 10.f, 5, 0, 7, 0, 32, 32);
    pAnimationComponent->AddAnimation(right1, 10.f, 8, 0, 11, 0, 32, 32);

    pAnimationComponent->AddAnimation(left0, 10.f, 5, 2, 7, 2, 32, 32);
    pAnimationComponent->AddAnimation(left1, 10.f, 8, 2, 11, 2, 32, 32);

    attackRightAnim = {right0, right1};
    attackLeftAnim = {left0, left1};
}

void Sword::test()
{
    1 + 1;
}

Sword::Sword() : Weapon(damage)
{

}
