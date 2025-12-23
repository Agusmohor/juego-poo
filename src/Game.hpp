#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "Pause.hpp"
#include <fstream>

class Game {
public:
    
    Game(scene* f_scene);
    ~Game();

    void run();
    void setScene(scene *newScene);
    void delPause();
    void isPaused(bool condition);

    void loadConfig(sf::RenderWindow &m_win);
    void makeConfig();
    void takeConfig(std::ifstream &file);

    const sf::Vector2u &getWinSize() const;
    const sf::View& getUIWinView() const;
private:
    sf::RenderWindow m_win;  
    scene *curr_scene; 
    scene *next_scene = nullptr;
    scene *m_pause = nullptr;
    sf::View m_view,m_uiview;
    bool ispaused;
    sf::Clock timer;
    sf::Vector2u resolution;
    std::string name;
    sf::Vector2u m_winSize;

    
};

#endif
