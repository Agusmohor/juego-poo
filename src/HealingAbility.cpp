#include "HealingAbility.hpp"
#include "Player.hpp"


void HealingAbility::update(float dt,player& p){
    if (cooldownTimer > 0.f) {cooldownTimer -= dt;}

    p.stateHeal();

    if(tryActive() && !(p.getHealth() >= 14)){p.startHeal();cooldownTimer = cooldownDur;p.setHealReady(false);}
    
    if (cooldownTimer <= 0.f) {p.setHealReady(true);}
}

bool HealingAbility::tryActive(){
    static bool prev = false;
    bool now = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F);
    bool isPressed = now && !prev;
    prev = now;
    return isPressed && cooldownTimer <= 0.f;
}


