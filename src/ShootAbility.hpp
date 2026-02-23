#pragma once
#ifndef SHOOTABILITY_H
#define SHOOTABILITY_H
#include "Ability.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class ShootAbility:public Ability{
    float cooldownDur = 8.f;
    float cooldownTimer = 0.f;
    float shootTimer = 0.f;
    float shootDur = 0.2;
public:
    void update(float dt, player& p) override;
    bool tryActive() override;
};
    
#endif