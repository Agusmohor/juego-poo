#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "Match.hpp"

class Game {
public:
    Game(match &f_scene);
    void run();
    void setScene(scene &new_scene);
private:
    sf::RenderWindow m_win;  
    match *curr_scene;
    scene *next_scene;
};

#endif
