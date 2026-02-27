#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "Pause.hpp"
#include "Stats.hpp"
#include <fstream>

struct keybinds {
    int shield, dash, fire, heal;
};


class game {
public:
    
    game(scene* f_scene);
    ~game();
    const sf::RenderWindow &getWindow();
    void run();

    void ProcessEvent();

    void setScene(scene *newScene);
    void Pause();
    void delPause();
    void isPaused(bool condition);

    void loadConfig(sf::RenderWindow &m_win);

    void makeProfile();

    void makeConfig();

    void makeKeybinds();

    void takeProfile(std::ifstream &file);

    void takeConfig(std::ifstream &file);

    const sf::Vector2u &getWinSize() const;
    const sf::View& getUIWinView() const;

    void setStats(const stats &m_stats);
    const stats &getStats();
    void setKeyBinds(const std::array<sf::Keyboard::Scancode,4>& keys, bool save);
    const std::array<sf::Keyboard::Scancode, 4>& getKeyBinds() const;

    void setPlayerSaves(const playerSaves& psaves);
    const playerSaves& getPlayerSaves() const;
    void setZombieSaves(const zombieSave& zsaves);
    const std::vector<zombieSave>& getZombieSaves() const;

    void clearZsaves();

    void clearTsaves();

    void setTreeSaves(const treeSave &tsave);
    const std::vector<treeSave>& getTreeSaves() const;

    void saveProgress();
    bool loadProgress();
    void newProgress();

    void setNewMatch(bool b);
    void exit();

    bool isNewMatch();
    void setSaveAndQuit(bool saq);
    bool getSaveAndQuit();
    void setIsOver(bool isover);
    bool getIsOver();
private:
    sf::RenderWindow m_win;
    scene* curr_scene = nullptr;
    scene* next_scene = nullptr;
    scene* m_pause = nullptr;
    sf::View m_view,m_uiview;
    bool ispaused = false;
    bool isExit = false;
    bool newMatch = false;
    sf::Clock timer,time;
    sf::Vector2u resolution;
    std::string name;
    sf::Vector2u m_winSize;
    stats m_lastStats;
    std::array<sf::Keyboard::Scancode,4> m_keys;

    bool saveAndQuit = false;
    bool isOver = false;
    keybinds kb;
    playerSaves player_saves;
    std::vector<zombieSave> zsaves;
    std::vector<treeSave> tsaves;
};

#endif
