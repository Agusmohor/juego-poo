#include "Pause.hpp"
#include "Match.hpp"
#include "Game.hpp"

match::match() : m_ply() , m_text("../assets/textures/fondo.jpg"), Fondo(m_text){}

void match::update(Game &m_gam){
    m_ply.update();
    match::doPause(m_gam);
}

void match::draw(sf::RenderWindow &m_win){
    m_win.clear();
    m_win.draw(Fondo);
    m_ply.draw(m_win);
}

void match::doPause(Game &m_gam){
    if (timer.getElapsedTime().asSeconds() >= 0.1f) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            m_gam.setScene(new PauseScene);
        }
        timer.restart();
    }
}