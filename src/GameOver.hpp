#ifndef JUEGO_POO_GAMEOVER_H
#define JUEGO_POO_GAMEOVER_H
#include "Scene.hpp"
#include "Game.hpp"

class gameover : public scene{
public:
    void update(float delta, Game &m_gam) override;
    void updateView(Game &m_gam) override;
    void draw(sf::RenderWindow &m_win) override;
    void getStats(const stats& s);
};

#endif