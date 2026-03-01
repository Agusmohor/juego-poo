#include "gameplay/HealingAbility.hpp"
#include "world/Player.hpp"


void HealingAbility::update(float dt,player& p){
    if (cooldownTimer > 0.f) {cooldownTimer -= dt;}

    key = p.getKey(action::heal);
    p.stateHeal();

    if(tryActive() && !(p.getHealth() >= 14)){p.startHeal();cooldownTimer = cooldownDur;p.setHealReady(false);}
    
    if (cooldownTimer <= 0.f) {p.setHealReady(true);}
}




