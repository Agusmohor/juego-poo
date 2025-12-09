#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

class player{
public:
    player();
    void update();
    void draw(sf::RenderWindow& m_win);
private:
    sf::Texture m_txt;
    sf::Sprite m_spr;
};


#endif