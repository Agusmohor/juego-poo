#ifndef JUEGO_POO_DASHABILITY_H
#define JUEGO_POO_DASHABILITY_H

#include <SFML/Window/Keyboard.hpp>

#include "Ability.hpp"

class DashAbility : public Ability {
    float cooldownDuration = 5.f;
    float dashTimer = 0.f;
    float dashDuration = 0.15f;
    bool active = false;
public:
    void update(float dt, player& p) override;
};


#endif