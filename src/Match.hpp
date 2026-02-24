#pragma once

#include "Scene.hpp"
#include "Player.hpp"
#include "Hud.hpp"
#include <SFML/System/Clock.hpp>
#include "Zombie.hpp"
#include "Mapa.hpp"
#include "obstacle.hpp"
#include "Tree.hpp"

struct Resources {
    sf::Texture tree1,tree2,tree3;
    sf::Texture Player, shadow;
    sf::Texture Zombie;
};

struct enemies {
    int max_enemies = 3;
    int min_enemies = 1;
    int const getMaxEnemies() {return max_enemies;}
    int const getMinEnemies() {return min_enemies;}
};

class match : public scene {
    bool ispressed = false;
    bool isgameover = false;

    float m_timeAlive = 0.f;
    float m_kills = 0.f;

    stats m_stats;
    mapa m_mapa;

    std::unique_ptr<player> m_ply;

    sf::Texture m_text;
    sf::Sprite Fondo;

    //vector de obstaculos para agregar arboles,rocas,etc
    std::vector<std::unique_ptr<obstacle>> m_obtacles;
    std::vector<sf::FloatRect> m_hitboxes;
    std::vector<sf::Sprite*> m_worldSprites;

    std::vector<std::unique_ptr<zombie>> m_zombies;
    void spawnEnemies();
    void spawnEnemies(int cant);

    void isOver();

    sf::View m_view,m_uiview;
    sf::Vector2u m_winSize;
    float spriteTimer = 0.f;
    float spriteDur = 0.1f;
    hud m_hud;

    enemies zombies;
    bool spawn = false;

    Resources m_res;

public:
    match();
    void doPause(Game &m_gam);
    void update(float delta,Game &m_gam) override;
    void updateView(Game &m_gam) override;
    void draw(sf::RenderWindow &m_win) override;
    void render(sf::RenderWindow &m_win);
    void mouseSkin(const sf::RenderWindow &m_win);
    bool attact(sf::RenderWindow &m_win,sf::FloatRect entpos);

    void normalView(sf::RenderWindow& m_win);

    void hits();
};
