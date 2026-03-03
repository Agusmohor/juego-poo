#pragma once
#ifndef SHOOTABILITY_H
#define SHOOTABILITY_H
#include "Ability.hpp"
#include <SFML/Window/Keyboard.hpp>

class ShootAbility : public Ability{
    float cooldownDur = 2.f;
    float cooldownTimer = 0.f;
    float shootTimer = 0.f;
    float shootDur = 0.2;
    sf::Keyboard::Scancode key = sf::Keyboard::Scancode::Unknown;
public:
    void update(float dt, player& p) override;
    bool tryActive() override;
};
    
#endif
