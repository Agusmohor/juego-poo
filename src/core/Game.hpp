#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();
private:
    sf::RenderWindow m_win;  
    sf::CircleShape m_shape;
};

#endif
