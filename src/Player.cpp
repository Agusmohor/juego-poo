#include "Player.hpp"
#include <iostream>

player::player() : m_txt("../assets/textures/prueba.png"), m_spr(m_txt), m_speed(5), stamina(200){
    if(!m_txt.loadFromFile("../assets/textures/prueba.png")) throw std::runtime_error("err");
    sf::Vector2f scl(5.f,5.f); m_spr.setScale(scl);
    dir.x = 0.f; dir.y = 0.f;
}

void player::draw(sf::RenderWindow& m_win) {
    m_win.draw(m_spr);
    player::viewCentre(m_win);
}

void player::m_key(){
    dir.x = 0.f; dir.y = 0.f;
    //speed
    player::speed();
    //interaccion teclas
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) dir.y = -1.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) dir.x = -1.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) dir.y = 1.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) dir.x = 1.f;
}

void player::speed(){
    m_speed = 5;
    if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && player::cond()) && stamina < 200){
        stamina++; 
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && stamina > 0 && player::cond()){
        stamina--; m_speed *= 2; 
    }
    std::cout << "stam " << stamina << " vel " << m_speed<<std::endl;
}

bool player::cond(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) return true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) return true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) return true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) return true;
    return false;
}

void player::m_mouse(){
    //interaccion mouse
}

void player::viewCentre(sf::RenderWindow &m_win){
    m_view.setCenter(pl_pos);
    m_win.setView(m_view);
}

void player::update() {
    //actualizar player
    player::m_key();
    m_spr.move(dir*m_speed);
    player::m_mouse();
    pl_pos=m_spr.getPosition();
}

