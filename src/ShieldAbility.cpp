#include "ShieldAbility.hpp"


#include "Player.hpp"

void ShieldAbility::update(float dt, player &p) {
    if (cooldownTimer > 0.f) {cooldownTimer -= dt;}
    key = p.getKey(action::shield);
    if (tryActive()) {p.shield(); cooldownTimer = cooldownDur; shieldTimer = shieldDur; p.setShieldReady(false);}
    if(p.getShieldActive()) {
        shieldTimer -= dt;
        if (shieldTimer <= 0 ) p.setShieldActive(false);
    }
    if (cooldownTimer <= 0.f) {p.setShieldReady(true);}
}

bool ShieldAbility::tryActive() {
    static bool prev = false;
    bool now ;
    if (key == sf::Keyboard::Scancode::Unknown){now = false;}
    now = sf::Keyboard::isKeyPressed(key);
    bool isPressed = now && !prev;
    prev = now;
    return isPressed && cooldownTimer <= 0.f;
}

