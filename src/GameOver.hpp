#ifndef JUEGO_POO_GAMEOVER_H
#define JUEGO_POO_GAMEOVER_H
#include "Scene.hpp"

class gameover : public scene{
    sf::RectangleShape shape;
    sf::Font font;
    sf::Text text,text2;
    bool isgameover = false;
    bool exitgame = false;
    bool mainmenu = false;
    stats m_stats;
    sf::Texture boton,botonselec;
    sf::RectangleShape returnToMainMenu, exit;
public:
    gameover();
    void update(float delta, game &m_gam) override;
    void draw(sf::RenderWindow &m_win) override;
    void ProcessEvent(game &game, sf::Event &event) override;
    void buttonPressed( type t) override;
    void toText();
};

#endif