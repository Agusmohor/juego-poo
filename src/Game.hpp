#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "Pause.hpp"

class Game {
public:
    Game(scene* f_scene);
    void run();
    void setScene(scene *newScene);
    void makePause();
    void makePause(scene *newScene);
    void delPause();
    void isPaused(bool condition);
    ~Game();
private:
    sf::RenderWindow m_win;  
    scene *curr_scene; 
    scene *next_scene = nullptr;
    scene *m_pause = nullptr;
    sf::View m_view;
    bool ispaused;
    sf::Clock timer;
    
};

#endif
