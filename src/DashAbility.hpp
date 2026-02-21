#ifndef JUEGO_POO_DASHABILITY_H
#define JUEGO_POO_DASHABILITY_H
#include <SFML/Window/Context.hpp>

#include <SFML/System/Clock.hpp>
#include "Ability.hpp"


class DashAbility : public Ability {
    sf::Clock cooldown;
public:
    void update(float dt, player& p) override;
    bool tryActive() override;
};


#endif