#include "Abilities.hpp"

void Abilities::update(float dt, player &p) {
    dash.update(dt, p);
    shield.update(dt, p);
    shoot.update(dt,p);
}
