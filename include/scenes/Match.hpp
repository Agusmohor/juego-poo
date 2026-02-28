#pragma once

#include "core/Scene.hpp"
#include "world/Player.hpp"
#include "ui/Hud.hpp"
#include <SFML/System/Clock.hpp>
#include "world/Zombie.hpp"
#include "world/Mapa.hpp"
#include "world/obstacle.hpp"
#include "core/Drawble.hpp"
#include "world/Tree.hpp"

struct Resources {
    sf::Texture tree1,tree2,tree3;
    sf::Texture Player, shadow, shield, fballskin;
    sf::Texture Zombie;
};

struct enemies {
    int max_enemies = 5;
    int min_enemies = 1;
    int minTilex = 20; int maxTilex = 47;
    int minTiley = 20; int maxTiley = 47;
    int minNTilex = 28; int maxNTilex = 41;
    int minNTiley = 25; int maxNTiley = 43;

    float spawnCooldownTimer = 0.f;
    float spawnCooldownDur = 0.6f;
    int const getMaxEnemies() const {return max_enemies;}
    int const getMinEnemies() const {return min_enemies;}
};

struct obstacles {
    int minTilex = 15; int maxTilex = 55;
    int minTiley = 15; int maxTiley = 55;
    int minNTilex = 34; int maxNTilex = 35;
    int minNTiley = 34; int maxNTiley = 35;
    int maxTreeSpawn = 500;
};

class match : public scene {
    bool ispressed = false;
    bool isgameover = false;

    float time = 0;
    int kills = 0;

    stats m_stats;
    mapa m_mapa;

    std::unique_ptr<player> m_ply;

    sf::Texture m_text;
    sf::Sprite Fondo;

    //vector de obstaculos para agregar arboles,rocas,etc
    std::vector<std::unique_ptr<obstacle>> m_obtacles;
    obstacles m_obs;
    void spawnObstacle();
    // void spawnObstacle();

    std::vector<sf::FloatRect> m_hitboxes;
    std::vector<drawble*> m_drawble;

    std::vector<std::unique_ptr<zombie>> m_zombies;
    void spawnEnemies();

    void isOver();

    sf::View m_view,m_uiview;
    sf::Vector2u m_winSize;
    float spriteTimer = 0.f;
    float spriteDur = 0.1f;
    hud m_hud;

    enemies zombies;
    bool spawn = false;

    Resources m_res;

    bool isRecentlyOpen = true;
    std::vector<zombieSave> m_zombieSave;
    std::vector<treeSave> m_treeSave;
    void ProcessEvent(game &game, sf::Event &event) override;
    void callSaveAndQuit(game &gam);
public:
    match();
    void doPause(game &m_gam);
    void update(float delta,game &m_gam) override;
    void updateView(game &m_gam) override;
    void draw(sf::RenderWindow &m_win) override;
    void render(sf::RenderWindow &m_win);
    bool attact(sf::RenderWindow &m_win,sf::FloatRect entpos);

    void normalView(sf::RenderWindow& m_win);

    void hits();

    void setPlayerKeyBinds(const std::array<sf::Keyboard::Scancode,4>& keyBinds);
    const playerSaves& getPlayerSave();

    const zombieSave& getZombieSave();
};
