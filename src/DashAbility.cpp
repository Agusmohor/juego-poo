#include "DashAbility.hpp"
#include "Player.hpp"
#include <iostream>

void DashAbility::update(float dt, player &p) {
    if (tryActive()) {p.dashMovement();}

}

bool DashAbility::tryActive() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) && cooldown.getElapsedTime().asSeconds() > 5) {
        cooldown.restart();return true;
    }
    return false;
}