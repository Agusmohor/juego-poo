#ifndef JUEGO_POO_ABILITIES_H
#define JUEGO_POO_ABILITIES_H
#include "Ability.hpp"
#include <vector>
#include "DashAbility.hpp"
#include "ShieldAbility.hpp"
#include "ShootAbility.hpp"
#include "HealingAbility.hpp"

class Ability;

class Abilities {
    std::vector<Ability> abilities;
    DashAbility dash;
    ShieldAbility shield;
    ShootAbility shoot;
    HealingAbility heal;
public:
    void update(float dt, player& p);

};


#endif