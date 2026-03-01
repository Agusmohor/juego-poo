#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "scenes/Pause.hpp"
#include "AudioManager.hpp"
#include "ConfigManager.hpp"
#include <fstream>




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
    std::string currName;
    sf::Vector2u m_winSize;
    stats p_stats;
    std::array<sf::Keyboard::Scancode,4> m_keys;

    bool saveAndQuit = false;
    bool isOver = false;
    playerSaves p_saves;
    std::vector<zombieSave> z_saves;
    std::vector<treeSave> t_saves;

    int volume;

    AudioManager audio;
    ConfigManager config;

    void ProcessEvent();


public:
    game(scene* f_scene);
    ~game();
    const sf::RenderWindow &getWindow() const;
    void run();
    void setScene(scene *newScene);

    void Pause();
    void delPause();

    AudioManager& getAudio();
    void newProgress();
    bool loadProgress();
    void saveProgress();
    void saveConfig();
    void loadConfig();

    const sf::Vector2u &getWinSize() const;
    const sf::View& getView() const;

    void setName(const std::string& name);

    void setStats(const stats &m_stats);
    const stats &getStats() const;
    void setKeyBinds(const std::array<sf::Keyboard::Scancode,4>& keys);
    const std::array<sf::Keyboard::Scancode, 4>& getKeyBinds() const;



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
