#ifndef JUEGO_POO_ABILITY_H
#define JUEGO_POO_ABILITY_H
#include <SFML/Window/Keyboard.hpp>

class player;

class Ability {
    public:
    virtual void update(float dt, player& p) = 0;
    virtual bool tryActive() = 0;
    virtual ~Ability() = default;
};


#endif