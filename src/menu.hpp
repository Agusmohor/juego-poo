
#ifndef MENU_HPP
#define MENU_HPP
#include "Scene.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class menu: public scene{
public:
    menu();
    void update()override;
    void draw(sf::RenderWindow &win)override;
private:
    sf::Font m_font;
    sf::Text m_text1,m_text2;
};

#endif