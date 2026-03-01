#ifndef JUEGO_POO_ABILITY_H
#define JUEGO_POO_ABILITY_H

#include <SFML/Window.hpp>
class player;

class Ability {
protected:
    sf::Keyboard::Scancode key = sf::Keyboard::Scancode::Unknown;
    float cooldownTimer = 0.f;
public:
    virtual void update(float dt, player& p) = 0;
    virtual bool tryActive() {
        static bool prev = false;
        bool now ;
        if (key == sf::Keyboard::Scancode::Unknown){now = false;}
        now = sf::Keyboard::isKeyPressed(key);
        bool isPressed = now && !prev;
        prev = now;
        return isPressed && cooldownTimer <= 0.f;    };
    virtual ~Ability() = default;
};


#endif