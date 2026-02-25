#include "HealingAbility.hpp"
#include "Player.hpp"


void HealingAbility::update(float dt,player& p){
    if (cooldownTimer > 0.f) {cooldownTimer -= dt;}

    if(tryActive()){p.doHeal();cooldownTimer = cooldownDur;}
    
    p.stateHeal();
}

bool HealingAbility::tryActive(){
    static bool prev = false;
    bool now = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F);
    bool isPressed = now && !prev;
    prev = now;
    return isPressed && cooldownTimer <= 0.f;
}


