#include "Player.hpp"
#include <cmath>
#include <iostream>

player::player() : m_txt("../assets/textures/prueba.png"),text1("../assets/textures/derecha.png"), text2("../assets/textures/izq.png"), text3("../assets/textures/abajoizq.png"), m_spr(m_txt),m_speed(5),stamina(200){
    if(!m_txt.loadFromFile("../assets/textures/prueba.png")) throw std::runtime_error("err");
    sf::Vector2f scl(5.f,5.f); m_spr.setScale(scl);
    dir.x = 0.f; dir.y = 0.f;
    wKey = sf::Keyboard::Key::W;aKey = sf::Keyboard::Key::A;sKey = sf::Keyboard::Key::S;dKey = sf::Keyboard::Key::D;
    rClick = sf::Mouse::Button::Right;
}

void player::move(){
    dir.x = 0.f; dir.y = 0.f;
    //speed
    this->speed();
    //interaccion teclas
    if(sf::Keyboard::isKeyPressed(wKey) && !sf::Keyboard::isKeyPressed(sKey)) dir.y = -1.f;  
    if(sf::Keyboard::isKeyPressed(aKey) && !sf::Keyboard::isKeyPressed(dKey)) dir.x = -1.f; 
    if(sf::Keyboard::isKeyPressed(sKey) && !sf::Keyboard::isKeyPressed(wKey)) dir.y = 1.f;  
    if(sf::Keyboard::isKeyPressed(dKey) && !sf::Keyboard::isKeyPressed(aKey)) dir.x = 1.f; 
}

void player::texture(){
    if(sf::Keyboard::isKeyPressed(wKey) && !sf::Mouse::isButtonPressed(rClick)) m_spr.setTexture(text2);
    if(sf::Keyboard::isKeyPressed(aKey) && !sf::Mouse::isButtonPressed(rClick)) m_spr.setTexture(text3);
    if(sf::Keyboard::isKeyPressed(sKey) && !sf::Mouse::isButtonPressed(rClick)) m_spr.setTexture(m_txt);
    if(sf::Keyboard::isKeyPressed(dKey) && !sf::Mouse::isButtonPressed(rClick)) m_spr.setTexture(text1);
}

void player::speed(){
    m_speed = 5;
    if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && this->cond()) && stamina < 200){
        stamina++; 
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && stamina > 0 && this->cond() && !sf::Mouse::isButtonPressed(rClick)){
        stamina--; m_speed *= 2; 
    }
    // std::cout << "stam " << stamina << " vel " << m_speed<<std::endl;
}

bool player::cond(){
    if(sf::Keyboard::isKeyPressed(wKey)) return true;
    if(sf::Keyboard::isKeyPressed(aKey)) return true;
    if(sf::Keyboard::isKeyPressed(sKey)) return true;
    if(sf::Keyboard::isKeyPressed(dKey)) return true;
    return false;
}

//movimiento enfoque mouse
void player::m_mouse(const sf::Vector2f &mouseCoords){
    //interaccion mouse
    //dx  //dx y dy, son las distancias entre el personaje, y el cursor en ese momento, (coords cursor - coords player)
    dx = mouseCoords.x - pl_pos.x; dy = mouseCoords.y - pl_pos.y;
    //angulo entre el player y el cursor (0-180)
    m_angle = atan2(dy,dx); m_angle *= 180 / 3.14;
    if(m_angle < 0 && m_angle > -90) m_spr.setTexture(text1); 
    if(m_angle <= -90 && m_angle >= -180) m_spr.setTexture(text2);
    if(m_angle > 90 && m_angle < 180) m_spr.setTexture(text3);
    if(m_angle <= 90 && m_angle >= 0) m_spr.setTexture(m_txt);
        
    // std::cout << "ang " << m_angle << " dx " << dx<< " dy " << dy << " posmouse " << mouseCoords.x << " x "<< mouseCoords.y << " y "<<std::endl;
    // std::cout << mouseCoords.x << " " << mouseCoords.y <<std::endl;aW
}

void player::update() {
    //actualizar player
    this->move();
    this->texture();
    m_spr.move(dir*m_speed);
    pl_pos=m_spr.getPosition();
}

void player::draw(sf::RenderWindow& m_win) {
    m_win.draw(m_spr);
}

void player::updateSkinByMouse(const sf::Vector2f &mouseCoords){
    this->m_mouse(mouseCoords);
}

//posicion del player
sf::Vector2f player::getPosition() const {
    return pl_pos;
}

