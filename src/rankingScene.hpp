#ifndef JUEGO_POO_RANKINGSCENE_H
#define JUEGO_POO_RANKINGSCENE_H

#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include <vector>
#include "Stats.hpp"
#include <fstream>

class rankingScene : public scene {
    std::vector<stats> m_list;
public:
    rankingScene();
    void update(float delta, game &m_gam) override;
    void draw(sf::RenderWindow &m_win) override;
    void load();
    void save(const stats& p);
    void createSave();
};


#endif