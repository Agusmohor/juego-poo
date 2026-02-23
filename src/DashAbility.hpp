#ifndef JUEGO_POO_DASHABILITY_H
#define JUEGO_POO_DASHABILITY_H

#include "Ability.hpp"


class DashAbility : public Ability {
    float cooldownDuration = 5.f;
    float cooldownTimer;
    bool active = false;
public:
    void update(float dt, player& p) override;
    bool tryActive() override;
};


#endif