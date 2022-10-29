
#ifndef UNTITLED7_WEAPON_H
#define UNTITLED7_WEAPON_H

#include "../../dependencies.h"

class Weapon
{
protected:
    std::vector<std::string> attackUpAnim, attackDownAnim;

    int damage;

public:
    Weapon(int damage);
    virtual ~Weapon();

    std::vector<std::string> attackRightAnim;
    std::vector<std::string> attackLeftAnim;

    virtual void test() = 0;
};


#endif //UNTITLED7_WEAPON_H
