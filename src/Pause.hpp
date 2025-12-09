
#ifndef PAUSE_HPP
#define PAUSE_HPP

#include "Scene.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>

class pause: public scene{
public:
    pause();
    void update(Game &m_gam)override;
    void draw(sf::RenderWindow &win)override;
private:
    sf::Font m_font;
    sf::Text m_text;
    sf::Clock timer;
};

#endif