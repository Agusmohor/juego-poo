#include "Player.hpp"

player::player() : m_txt("../assets/textures/prueba.png"), m_spr(m_txt) {
    if(!m_txt.loadFromFile("../assets/textures/prueba.png")) throw std::runtime_error("err");
    m_spr.setTexture(m_txt);
    sf::Vector2f scl(10.f,10.f);
    m_spr.setScale(scl);
    m_spr.setPosition({300,300});
}

void player::draw(sf::RenderWindow& m_win){
    m_win.draw(m_spr);
}

void player::m_key(){
    //interaccion teclas
    sf::Vector2f offsetx(0.2,0);
    sf::Vector2f offsety(0,0.2);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) m_spr.move(-offsety);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) m_spr.move(-offsetx);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) m_spr.move(offsety);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) m_spr.move(offsetx);
}

void player::m_mouse(){
    //interaccion mouse
}

void player::update(){
    //actualizar player
    player::m_key();
    player::m_mouse();
}

