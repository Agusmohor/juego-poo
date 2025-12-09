#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Scene.hpp"

class Game {
public:
    Game(scene* f_scene);
    void run();
    void setScene(scene *new_scene);
    ~Game();
private:
    sf::RenderWindow m_win;  
    scene *curr_scene;
};

#endif
