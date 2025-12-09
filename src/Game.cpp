#include "Game.hpp"

Game::Game(scene* f_scene) : m_win(sf::VideoMode({800,800}), "Juego Poo"), curr_scene(f_scene){
    // m_win.setFramerateLimit(120);
}

void Game::run(){
    while(m_win.isOpen()){
        // ve todos los eventos q ocurren en la ventana
        while(const auto evt = m_win.pollEvent()){
            //evento cerrar ventana
            if(evt->is<sf::Event::Closed>()) m_win.close();
        }
        curr_scene->update(*this);
        curr_scene->draw(m_win);
        m_win.display();
    }

}

void Game::setScene(scene * new_scene){
    delete curr_scene;
    curr_scene = new_scene;
}

Game::~Game(){
    delete curr_scene;
}