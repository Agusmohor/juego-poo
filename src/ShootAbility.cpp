#include "ShootAbility.hpp"
#include "Player.hpp"
#include <iostream>

void ShootAbility::update(float dt,player& p){
    p.shootState();
    if (cooldownTimer > 0.f) {cooldownTimer -= dt;}

    if(tryActive()){p.doShoot();cooldownTimer = cooldownDur; shootTimer = shootDur;}
    if(p.getShootActive()) {
        shootTimer -= dt;
        if (shootTimer <= 0 ) p.setShootActive(false);
    }
}

bool ShootAbility::tryActive(){
    static bool prev = false;
    bool now = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R);
    bool isPressed = now && !prev;
    prev = now;
    return isPressed && cooldownTimer <= 0.f;
}



   

