#include "Game.hpp"
#include "Player.hpp"

player m_spr;

Game::Game() : m_win(sf::VideoMode({800,800}), "Juego Poo"){
}

void Game::run(){
    while(m_win.isOpen()){
        // ve todos los eventos q ocurren en la ventana
        while(const auto evt = m_win.pollEvent()){
            //evento cerrar ventana
            if(evt->is<sf::Event::Closed>()) m_win.close();
        }
        m_win.clear();
        m_spr.update();
        m_spr.draw(m_win);
        m_win.display();
    }

}