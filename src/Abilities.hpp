#ifndef JUEGO_POO_ABILITIES_H
#define JUEGO_POO_ABILITIES_H
#include "Ability.hpp"
#include <vector>
#include "DashAbility.hpp"

class Ability;

class Abilities {
    std::vector<Ability> abilities;
    DashAbility dash;
public:
    void update(float dt, player& p);

};


#endif