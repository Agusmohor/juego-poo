#include "ShootAbility.hpp"
#include "Player.hpp"
#include <iostream>

void ShootAbility::update(float dt,player& p){
    p.shootState(dt);
    if (cooldownTimer > 0.f) {cooldownTimer -= dt;}

    if(tryActive()){p.startShoot();cooldownTimer = cooldownDur; shootTimer = shootDur;p.setFireReady(false);}
    if(p.getShootActive()) {
        shootTimer -= dt;
        if (shootTimer <= 0 ) p.setShootActive(false);
    }
    if (cooldownTimer <= 0.f) {p.setFireReady(true);}
}

bool ShootAbility::tryActive(){
    static bool prev = false;
    bool now = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
    bool isPressed = now && !prev;
    prev = now;
    return isPressed && cooldownTimer <= 0.f;
}

   

