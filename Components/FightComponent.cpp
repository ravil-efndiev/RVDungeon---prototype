
#include "FightComponent.h"

FightComponent::FightComponent(AnimationComponent* pAnimationComponent)
    : pAnimationComponent(pAnimationComponent)
{
    maxCount = 1;
    currentAttack = 0;
    madeAttacks = 0;
}

FightComponent::~FightComponent() {}

void FightComponent::Start()
{
    attack = true;
}

const bool FightComponent::GetAttack()
{
    return attack;
}

void FightComponent::Update(MoveDirections direction, const float& deltaTime)
{

    switch (direction)
    {
        case MoveDirections::right:
            pAnimationComponent->Play(rightAnimNames[currentAttack], deltaTime);
            break;
        case MoveDirections::left:
            pAnimationComponent->Play(leftAnimNames[currentAttack], deltaTime);
            break;       
        case MoveDirections::up:
            pAnimationComponent->Play(rightAnimNames[currentAttack], deltaTime);
            break;
        case MoveDirections::down:
            pAnimationComponent->Play(leftAnimNames[currentAttack], deltaTime);
            break;
    }

    if (pAnimationComponent->IsDone())
    {
        attack = false;
        if (currentAttack == 0) madeAttacks++;
        if (currentAttack == 1) currentAttack = 0;
    }
}

void FightComponent::FixedUpdate(const float &deltaTime)
{
    if (currentAttack == 0)
    {
        if (madeAttacks > 0)
        {
            count += deltaTime;
            if (count >= maxCount)
            {
                currentAttack = 0;
                madeAttacks = 0;
                count = 0;
            }
            else if (attack)
            {
                currentAttack = 1;
                madeAttacks = 0;
                count = 0;
                return;
            }
        }
        else
            currentAttack = 0;
    }
}

void FightComponent::SetWeapon(Weapon *weapon)
{
    this->rightAnimNames = weapon->attackRightAnim;
    this->leftAnimNames = weapon->attackLeftAnim;
}
