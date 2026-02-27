#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "Pause.hpp"
#include <fstream>

struct keybinds {
    int shield, dash, fire, heal;
};

class Game {
public:
    
    Game(scene* f_scene);
    ~Game();

    void run();

    void ProcessEvent();

    void setScene(scene *newScene);
    void Pause();
    void delPause();
    void isPaused(bool condition);

    void loadConfig(sf::RenderWindow &m_win);
    void makeConfig();

    void makeKeybinds();

    void takeConfig(std::ifstream &file);

    const sf::Vector2u &getWinSize() const;
    const sf::View& getUIWinView() const;

    void setStats(const stats &m_stats);
    const stats &getStats();
    void setKeyBinds(const std::array<sf::Keyboard::Scancode,4>& keys, bool save);
    const std::array<sf::Keyboard::Scancode, 4>& getKeyBinds() const;
private:
    sf::RenderWindow m_win;
    scene* curr_scene = nullptr;
    scene* next_scene = nullptr;
    scene* m_pause = nullptr;
    sf::View m_view,m_uiview;
    bool ispaused = false;
    sf::Clock timer,time;
    sf::Vector2u resolution;
    std::string name;
    sf::Vector2u m_winSize;
    stats m_lastStats;
    std::array<sf::Keyboard::Scancode,4> m_keys;

    keybinds kb;
};

#endif
