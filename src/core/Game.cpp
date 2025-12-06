#include "Game.hpp"

Game::Game() : m_win(sf::VideoMode({800,800}), "Juego Poo"){
    m_spr.setRadius(100.f);
    m_shape.setFillColor(sf::Color::Green);
}

void Game::run(){
    while(m_win.isOpen()){
        while(const auto evt = m_win.pollEvent()){
            if(evt->is<sf::Event::Closed>()) m_win.close();
        }
        m_win.clear();
        m_win.draw(m_shape);
        m_win.display();
    }

}