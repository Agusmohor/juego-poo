#include "Game.hpp"

Game::Game() : m_win(sf::VideoMode({800,800}), "Juego Poo"){
    m_shape.setRadius(100.f);
    m_shape.setFillColor(sf::Color::Green);
}

void Game::run(){
    while(m_win.isOpen()){
        while(auto evt = m_win.pollEvent()){
            if(evt->is<sf::Event::Closed>()) m_win.close();
        }
    }
        
}