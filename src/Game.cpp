#include "Game.hpp"

Game::Game(match &f_scene) : m_win(sf::VideoMode({800,800}), "Juego Poo") {
    curr_scene = &f_scene;
}

void Game::run(){
    while(m_win.isOpen()){
        // ve todos los eventos q ocurren en la ventana
        while(const auto evt = m_win.pollEvent()){
            //evento cerrar ventana
            if(evt->is<sf::Event::Closed>()) m_win.close();
        }
        m_win.clear(sf::Color(220,220,180,255));
        curr_scene->update();
        curr_scene->draw(m_win);
        m_win.display();
    }

}