#ifndef JUEGO_POO_SETTINGSSCENE_H
#define JUEGO_POO_SETTINGSSCENE_H
#include "Scene.hpp"
#include "Keys.hpp"

enum struct type {
    resume,
    setting,
    exit,
    Ab1, Ab2, Ab3, Ab4
};



class settingsScene : public scene{
    sf::RectangleShape background, Ab1,Ab2,Ab3,Ab4;
    sf::Texture boton,botonselec;
    sf::Font font; sf::Text ab1Text,ab2Text,ab3Text,ab4Text;
    std::array<sf::Keyboard::Key,4> m_keys;



    void button_overlay(const sf::RenderWindow &win, sf::RectangleShape &button, type t);
public:
    settingsScene();
    void update(float delta,Game &m_gam) override;
    void ProcessEvent(Game &game, sf::Event &event) override;
    void updateView(Game &m_gam) override;
    void draw(sf::RenderWindow &m_win) override;
    void setKey(action action);
};


#endif