#pragma once
#ifndef HEALINGABILITY_H
#define HEALINGABILITY_H

#include "Ability.hpp"

class HealingAbility: public Ability{
    float cooldownDur = 10.f;
    float cooldownTimer = 0.f;
public:
    void update(float dt, player& p) override;
    bool tryActive() override;
};
    
#endif