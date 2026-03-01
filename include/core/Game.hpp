#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "scenes/Pause.hpp"
#include "gameplay/Stats.hpp"
#include "core/AudioManager.hpp"
#include <fstream>

struct keybinds {
    int shield, dash, fire, heal;
};


class game {
    sf::RenderWindow m_win;
    scene* curr_scene = nullptr;
    scene* next_scene = nullptr;
    scene* m_pause = nullptr;
    sf::View m_view;
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

    int volume;

    AudioManager audio;

    void ProcessEvent();
    void loadConfig(sf::RenderWindow &m_win);

    void takeProfile(std::ifstream &file);
    void takeConfig(std::ifstream &file);

    void makeProfile();
    void makeConfig();
    void makeKeybinds();

    void saveProgress();

public:
    game(scene* f_scene);
    ~game();
    const sf::RenderWindow &getWindow() const;
    void run();
    void setScene(scene *newScene);

    void Pause();
    void delPause();

    AudioManager& getAudio();

    const sf::Vector2u &getWinSize() const;
    const sf::View& getView() const;

    void setStats(const stats &m_stats);
    const stats &getStats() const;
    void setKeyBinds(const std::array<sf::Keyboard::Scancode,4>& keys);
    const std::array<sf::Keyboard::Scancode, 4>& getKeyBinds() const;

    bool loadProgress();
    void newProgress();

    void setPlayerSaves(const playerSaves& psaves);
    const playerSaves& getPlayerSaves() const;
    void clearZsaves();
    void setZombieSaves(const zombieSave& zsaves);
    const std::vector<zombieSave>& getZombieSaves() const;
    void clearTsaves();
    void setTreeSaves(const treeSave &tsave);
    const std::vector<treeSave>& getTreeSaves() const;

    void setNewMatch(bool b);
    void exit();
    bool isNewMatch();
    void setSaveAndQuit(bool saq);
    bool getSaveAndQuit();
    void setIsOver(bool isover);
    bool getIsOver();

    void setVolume(int vol);
    int getVolume() const;
};

#endif
