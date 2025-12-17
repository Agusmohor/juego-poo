#pragma once
#ifndef PAUSE_HPP
#define PAUSE_HPP

#include "Scene.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Game.hpp"

class PauseScene : public scene{
public:
    PauseScene();
    void update(Game &m_gam)override;
    void draw(sf::RenderWindow &win)override;
    void backMatch(Game &m_gam);
private:
    sf::Font m_font;
    sf::Text m_text;
    sf::RectangleShape overlay;
};

#endif