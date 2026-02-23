#ifndef JUEGO_POO_SHIELDABILITY_H
#define JUEGO_POO_SHIELDABILITY_H

#include "Ability.hpp"

class ShieldAbility : public Ability {
    float cooldownDur = 5.f;
    float cooldownTimer = 0.f;
    float shieldTimer = 0.f;
    float shieldDur = 3.f;
    bool active = false;
public:
    void update(float dt, player &p) override;
    bool tryActive() override;
};


#endif