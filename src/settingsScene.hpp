#ifndef JUEGO_POO_SETTINGSSCENE_H
#define JUEGO_POO_SETTINGSSCENE_H
#include "Scene.hpp"

enum struct type {
    resume,
    setting,
    exit,
    Ab1, Ab2, Ab3, Ab4
};

class settingsScene : public scene{
    sf::RectangleShape background, Ab1,Ab2,Ab3,Ab4;
    sf::Texture boton,botonselec;


    void button_overlay(const sf::RenderWindow &win, sf::RectangleShape &button, type t);
public:
    settingsScene();
    void update(float delta,Game &m_gam) override;
    void updateView(Game &m_gam) override;
    void draw(sf::RenderWindow &m_win) override;
};


#endif