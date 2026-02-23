#include "DashAbility.hpp"
#include "Player.hpp"
#include <iostream>

void DashAbility::update(float dt, player &p) {
    if (cooldownTimer > 0.f) cooldownTimer -= dt;

    if (tryActive()) {p.dashMovement(); cooldownTimer = cooldownDuration;}

}

bool DashAbility::tryActive() {
    static bool prev = false;
    bool now = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);
    bool isPressed = now && !prev;
    prev = now;
    return isPressed && cooldownTimer <= 0.f;
}