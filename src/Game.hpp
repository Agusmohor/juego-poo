#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "Match.hpp"

class Game {
public:
    Game(scene* f_scene);
    void run();
    void setScene(scene &new_scene);
private:
    sf::RenderWindow m_win;  
    scene *curr_scene;
    scene *next_scene;
};

#endif
