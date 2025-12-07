#include "Player.hpp"

player::player(){
    m_spr.setRadius(100.f);
    m_spr.setFillColor(sf::Color::Green);
}

void player::draw(sf::RenderWindow& m_win){
    m_win.draw(m_spr);
}

void player::update(){
    sf::Vector2f offsetx(0.5,0);
    sf::Vector2f offsety(0,0.5);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) m_spr.move(-offsety);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) m_spr.move(-offsetx);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) m_spr.move(offsety);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) m_spr.move(offsetx);
}

void player::move(){

}