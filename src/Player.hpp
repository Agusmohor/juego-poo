#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

class player{
public:
    player();
    void update();
    void draw(sf::RenderWindow& m_win);
    void m_mouse();
    void m_key();
private:
    sf::Texture m_txt;
    sf::Sprite m_spr;
    
};

#endif