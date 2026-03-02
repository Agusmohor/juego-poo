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

struct enemiesSpawn {
    int max_enemies = 5;
    int min_enemies = 1;
    //rango de aparicion
    int minTilex = 20; int maxTilex = 47;
    int minTiley = 20; int maxTiley = 47;
    //rango de no aparicion(zona prohibida)
    int minNTilex = 28; int maxNTilex = 41;
    int minNTiley = 25; int maxNTiley = 43;

    float spawnCooldownTimer = 0.f;
    float spawnCooldownDur = 0.6f;
    int const getMaxEnemies() const {return max_enemies;}
    int const getMinEnemies() const {return min_enemies;}
};

struct obstaclesSpawn {
    int minTilex = 15; int maxTilex = 55;
    int minTiley = 15; int maxTiley = 55;
    int minNTilex = 34; int maxNTilex = 35;
    int minNTiley = 34; int maxNTiley = 35;
    int maxTreeSpawn = 500;
};

struct playerSpawn {
    int minTileX = 25;
    int minTileY = 25;
    int maxTileX = 43;
    int maxTileY = 43;
    float maxDist = 100.f;
    float dist = 0.f;
    bool isOut = false;
    float timer = 10.f;
    float cooldownTimer = 0.f;
    float cooldownDur = 0.6f;
};

class match : public scene {

    bool ispressed = false;
    bool isgameover = false;

    bool isplaying = false;
    bool wasplaying = false;

    float time = 0;
    int kills = 0;

    hud m_hud;
    sf::RectangleShape WarningOverlay;
    sf::Font font;
    sf::Text t_waring;

    sf::View m_view,m_uiview;
    sf::Vector2u m_winSize;

    Resources m_res;
    obstaclesSpawn obs_spawn;
    enemiesSpawn z_spawn;
    playerSpawn p_spawn;
    stats m_stats;
    mapa m_mapa;

    std::unique_ptr<player> m_ply;
    std::vector<std::unique_ptr<zombie>> m_zombies;
    std::vector<std::unique_ptr<obstacle>> m_obtacles;

    bool drawHitbox = false;
    std::vector<drawble*> m_drawble;

    std::vector<sf::FloatRect> m_hitboxes;

    float spriteTimer = 0.f;
    float spriteDur = 0.1f;

    bool spawn = false;

    bool isRecentlyOpen = true;
    std::vector<zombieSave> m_zombieSave;
    std::vector<treeSave> m_treeSave;

    void render(sf::RenderWindow &m_win);
    void normalView(sf::RenderWindow& m_win);
    void hits();
    void ProcessEvent(game &game, sf::Event &event) override;
    void callSaveAndQuit(game &gam);
    void spawnObstacle();
    void spawnEnemies();
    void isOver();
    void specialFunctions(sf::RenderWindow &win);
    void playerIsOutOfRange(float delta);
public:
    match();
    void update(float delta,game &m_gam) override;
    void updateView(game &m_gam) override;
    void draw(sf::RenderWindow &m_win) override;

    void setPlayerKeyBinds(const std::array<sf::Keyboard::Scancode,4>& keyBinds);

};
