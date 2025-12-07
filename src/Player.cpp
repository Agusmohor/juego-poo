#include "Player.hpp"

player::player(){
    m_spr.setRadius(100.f);
    m_spr.setFillColor(sf::Color::Green);
}

void player::draw(sf::RenderWindow& m_win){
    m_win.draw(m_spr);
}

void player::update(){
    sf::Vector2f offsetx(0.2,0);
    sf::Vector2f offsety(0,0.2);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) m_spr.move(-offsety);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) m_spr.move(-offsetx);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) m_spr.move(offsety);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) m_spr.move(offsetx);
}

