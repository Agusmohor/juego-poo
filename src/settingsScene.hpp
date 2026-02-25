#ifndef JUEGO_POO_SETTINGSSCENE_H
#define JUEGO_POO_SETTINGSSCENE_H
#include "Scene.hpp"

class settingsScene : public scene{
public:
    settingsScene();
    void update(float delta,Game &m_gam) override;
    void updateView(Game &m_gam) override;
    void draw(sf::RenderWindow &m_win) override;
};


#endif