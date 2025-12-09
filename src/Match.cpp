#include "Match.hpp"

match::match() : m_ply() {}

void match::update(){
    m_ply.update();
}

void match::draw(sf::RenderWindow &m_win){
    m_ply.draw(m_win);
}