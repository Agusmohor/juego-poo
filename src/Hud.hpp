#pragma once
#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>

class hud{
public:
    hud();
    void update();
    void draw(sf::RenderWindow &m_win);
    void keyBoard();
    void moveHotbar(const sf::Vector2f &winview);
private:
    sf::Texture hobTexture,hselTe;
    sf::Sprite hotbarBar, hsel;
    sf::Keyboard::Key k_1,k_2,k_3,k_4,k_5,k_6;
    sf::Vector2f m_winSize,hselpos;
    int newpos;
};

#endif