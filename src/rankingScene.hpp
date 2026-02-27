#ifndef JUEGO_POO_RANKINGSCENE_H
#define JUEGO_POO_RANKINGSCENE_H

#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include <vector>
#include "Stats.hpp"
#include <fstream>

class rankingScene : public scene {
    sf::RectangleShape backButton;
    sf::Texture boton,botonselec;
    sf::Font font;
    sf::Text backText, title;
    std::vector<stats> m_list;
    bool backmain = false;
public:
    rankingScene();
    void update(float delta, game &m_gam) override;
    void draw(sf::RenderWindow &m_win) override;
    void buttonPressed(type t) override;
    void ProcessEvent(game &game, sf::Event &event) override;

    void load();
    void sortList();
    void save(const stats& p);
    void showVector(sf::RenderWindow &m_win);
    void createSave();
    bool getBackRequest();
    void setBackRequest(bool back);
};


#endif