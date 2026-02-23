#include "DashAbility.hpp"
#include "Player.hpp"
#include <iostream>

void DashAbility::update(float dt, player &p) {
    if (cooldownTimer > 0.f) cooldownTimer -= dt;

    if (tryActive()) {p.dashMovement(); cooldownTimer = cooldownDuration;}

}

bool DashAbility::tryActive() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) && cooldownTimer <= 0.f) {return true;}
    return false;
}