#pragma once
#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>

class hud{
public:
    hud();
    void update();
    void draw(sf::RenderWindow &m_win);
private:
    sf::Texture hobTexture;
    sf::Sprite hotbarBar;
};

#endif