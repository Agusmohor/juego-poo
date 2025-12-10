#pragma once
#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class hud{
public:
    hud();
    void update();
    void draw(sf::RenderWindow &m_win);
    std::vector<sf::Sprite> bar;
private:
    sf::Texture hobTexture,hselTe;
    sf::Sprite hotbarBar, hsel;
};

#endif