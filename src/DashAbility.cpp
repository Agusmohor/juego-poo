#include "DashAbility.hpp"
#include "Player.hpp"

void DashAbility::update(float dt, player &p) {
    if (tryActive()) p.dashMovement();
}

bool DashAbility::tryActive() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)){return true;}
    else{return false;}
}
