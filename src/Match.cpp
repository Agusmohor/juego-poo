#include "Match.hpp"
#include "Game.hpp"

match::match() : m_ply() {}

void match::update(Game &m_gam){
    m_ply.update();
}

void match::draw(sf::RenderWindow &m_win){
    m_win.clear(sf::Color(220,220,180,255));
    m_ply.draw(m_win);
}