#include "DashAbility.hpp"
#include "Player.hpp"

void DashAbility::update(float dt, player &p) {
    if (cooldownTimer > 0.f) cooldownTimer -= dt;

    if (tryActive()) {p.dashMovement(); cooldownTimer = cooldownDuration; dashTimer = dashDuration;p.setDashReady(false);}
    if (p.getDashActive()) {
        dashTimer -= dt;
        p.startDash(dt);
        if (dashTimer <= 0) p.setDashActive(false);
    }
    if (cooldownTimer <= 0.f) {p.setDashReady(true);}
}

bool DashAbility::tryActive() {
    static bool prev = false;
    bool now = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);
    bool isPressed = now && !prev;
    prev = now;
    return isPressed && cooldownTimer <= 0.f;
}
