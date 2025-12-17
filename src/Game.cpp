#include "Game.hpp"
#include <iostream>

Game::Game(scene* f_scene) : m_win(sf::VideoMode({800,800}), "Juego Poo"), curr_scene(f_scene), ispaused(false){
    m_win.setFramerateLimit(60);
}

void Game::run(){
    while(m_win.isOpen()){
        // ve todos los eventos q ocurren en la ventana
        while(const auto evt = m_win.pollEvent()){
            //evento cerrar ventana
            if(evt->is<sf::Event::Closed>()) m_win.close();
        }

        m_win.clear();

        if(!ispaused) curr_scene->update(*this);
        if(ispaused) m_pause->update(*this); 

        curr_scene->draw(m_win);
        if(ispaused && m_pause) m_pause->draw(m_win);

        m_win.display();
        if(next_scene){
            delete curr_scene;
            curr_scene = next_scene;
            next_scene = nullptr;
        }
    }

}

void Game::setScene(scene *newScene){
    next_scene = newScene;
}

Game::~Game(){
    delete curr_scene;
    delete next_scene;
    delete m_pause;
}

void Game::isPaused(bool condition){
    if (timer.getElapsedTime().asSeconds() >= 0.2f) {
        if(condition && !ispaused){ m_pause = new PauseScene; } 
        else{ Game::delPause(); }
        ispaused = condition;
    }
    timer.restart();
}

void Game::delPause(){
    delete m_pause;
    m_pause = nullptr;
}