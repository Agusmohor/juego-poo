#pragma once
#ifndef HEALINGABILITY_H
#define HEALINGABILITY_H

#include "Ability.hpp"
#include <SFML/Window/Keyboard.hpp>

class HealingAbility: public Ability{
    float cooldownDur = 10.f;
public:
    void update(float dt, player& p) override;
};
    
#endif