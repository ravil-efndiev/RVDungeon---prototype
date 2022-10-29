
#ifndef RPG_FIGHTCOMPONENT_H
#define RPG_FIGHTCOMPONENT_H

#include "AnimationComponent.h"
#include "../dependencies.h"
#include "../Entities/elements/weapons.h"

class FightComponent
{
private:
    bool attack;
    int currentAttack, madeAttacks;
    float count, maxCount;
    std::vector<std::string> leftAnimNames, rightAnimNames;
    AnimationComponent* pAnimationComponent;

public:
    FightComponent(AnimationComponent *pAnimationComponent);
    virtual ~FightComponent();

    void Start();
    void Update(MoveDirections direction, const float& deltaTime);
    void FixedUpdate(const float& deltaTime);

    void SetWeapon(Weapon* weapon);
    const bool GetAttack();
};


#endif
