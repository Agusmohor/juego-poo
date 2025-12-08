#pragma once
#ifndef MENU_HPP
#define MENU_HPP
#include "Scene.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

class menu : public scene{
public:
    menu();
    void update(Game &m_gam)override;
    void draw(sf::RenderWindow &win)override;
private:
    sf::Font m_font;
    sf::Text m_text1,m_text2;
};

#endif