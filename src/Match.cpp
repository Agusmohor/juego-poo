#include "Match.hpp"
#include "Game.hpp"

match::match() : m_ply() , m_text("../assets/textures/fotito.jpg"),Fondo(m_text){}

void match::update(Game &m_gam){
    m_ply.update();
}

void match::draw(sf::RenderWindow &m_win){
    m_win.clear();
    m_win.draw(Fondo);
    m_ply.draw(m_win);
}