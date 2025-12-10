#include "menu.hpp"
#include "Match.hpp"
#include "Game.hpp"

menu::menu() : m_font("../assets/fonts/fuente.ttf"),m_text1(m_font,"Jueguito"),m_text2(m_font,"press Enter to start"){
    m_text1.setCharacterSize(100);
    sf::Vector2f v(220,150);
    m_text1.setPosition(v);

    m_text2.setCharacterSize(30);
    m_text2.setFillColor(sf::Color(150,150,150));
    sf::Vector2f g(250,450);
    m_text2.setPosition(g);
}

void menu::update(Game &m_gam){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) m_gam.setScene(new match);
    if (timer.getElapsedTime().asSeconds() >= 0.28f) {
        // cambiar color
        r=rand();b=rand();g=rand();
        m_text1.setFillColor(sf::Color(r,g,b));
        timer.restart();
    }
    
}

void menu::draw(sf::RenderWindow &m_win){
    m_win.clear(sf::Color::Black);
    m_win.draw(m_text1);
    m_win.draw(m_text2);
}