#include "menu.hpp"

menu::menu():m_font("../assets/fonts/Bitcount_Prop_Single/Static/BitcountPropSingle-Regular.ttf"),m_text1(m_font,"Jueguito"),m_text2(m_font,"press Enter to start"){
    m_text1.setCharacterSize(50);
    m_text1.setFillColor(sf::Color::White);
    sf::Vector2f v(180,150);
    m_text1.setPosition(v);

    m_text2.setCharacterSize(30);
    m_text2.setFillColor(sf::Color::White);
    sf::Vector2f g(150,350);
    m_text2.setPosition(g);
}
void menu:: update(){

}
void menu::draw(sf::RenderWindow &win){
    win.clear(sf::Color::Black);
    win.draw(m_text1);
    win.draw(m_text2);
}