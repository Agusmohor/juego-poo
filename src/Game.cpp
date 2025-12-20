#include "Game.hpp"
#include <iostream>

Game::Game(scene* f_scene) : m_win(sf::VideoMode({800,800}), "Juego Poo"), curr_scene(f_scene), ispaused(false){
    m_win.setFramerateLimit(60);
    this->loadConfig(m_win);
}

void Game::run(){
    while(m_win.isOpen()){

        // ve todos los eventos q ocurren en la ventana
        while(const auto evt = m_win.pollEvent()){
            //evento cerrar ventana
            if(evt->is<sf::Event::Closed>()) m_win.close();
            if(const auto* resized = evt->getIf<sf::Event::Resized>()){
                m_winSize = sf::Vector2u(resized->size);
                sf::FloatRect visibleArea({0.f,0.f},sf::Vector2f(m_winSize));
                //centra la view cuando se hace un resize de la window
                m_view = sf::View(visibleArea); m_view.setCenter(m_win.getDefaultView().getCenter());
                m_uiview = sf::View(visibleArea); m_uiview.setCenter(m_win.getDefaultView().getCenter());
                m_win.setView(m_view);
            }
        }

        m_win.clear();

        if(!ispaused) curr_scene->update(*this);
        curr_scene->updateView(*this);
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
        else{ this->delPause(); }
        ispaused = condition;
    }
    timer.restart();
}

void Game::delPause(){
    delete m_pause;
    m_pause = nullptr;
}

void Game::loadConfig(sf::RenderWindow &m_win){
    std::ifstream file("../data/config/config.txt");
    if(!file.is_open()) this->makeConfig();
    file.close();
    file.open("../data/config/config.txt");
    this->takeConfig(file);
    m_win.setSize(resolution);
}

void Game::makeConfig(){
    std::ofstream cfile("../data/config/config.txt");
    cfile << "Resolution = 800x800" << std::endl;
    cfile << "Name = null" << std::endl;
    cfile.close();
}

void Game::takeConfig(std::ifstream &file){
    std::string aux;
    std::getline(file,aux); 
    resolution.x = std::stoi(aux.substr(aux.find("=")+1,(aux.find("x")-aux.find("=")+1)));
    resolution.y = std::stoi(aux.substr(aux.find("x")+1));
    std::getline(file,aux);
    name = aux.substr(aux.find("=")+1);
}

const sf::Vector2u& Game::getWinSize(){
    return m_winSize;
}

const sf::View& Game::getUIWinView(){
    return m_uiview;
}

