#ifndef JUEGO_POO_GAMEOVER_H
#define JUEGO_POO_GAMEOVER_H
#include "Scene.hpp"

struct sStats {
    sStats(const sf::Font& t);
    sf::Text time;
    sf::Text kills;
};

class gameover : public scene{
    sf::RectangleShape shape;
    sf::Font font;
    sf::Text text;
    bool isgameover = false;
    stats m_stats;
    sStats m_stats2;
public:
    gameover();
    void update(float delta, Game &m_gam) override;
    void updateView(Game &m_gam) override;
    void draw(sf::RenderWindow &m_win) override;

    void toText();
};

#endif