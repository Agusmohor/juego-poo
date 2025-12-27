#include "Player.hpp"
#include <cmath>
#include "Mapa.hpp"
#include <iostream>

player::player() : m_txt("../assets/textures/prueba.png"),text1("../assets/textures/derecha.png"), text2("../assets/textures/izq.png"), text3("../assets/textures/abajoizq.png"), m_spr(m_txt),m_speed(5),stamina(200){
    if(!m_txt.loadFromFile("../assets/textures/prueba.png")) throw std::runtime_error("err");
    // m_spr.setScale({1,1});
    m_spr.setOrigin({8,8}); m_spr.setPosition({80,80});
    dir.x = 0.f; dir.y = 0.f;
    wKey = sf::Keyboard::Key::W;aKey = sf::Keyboard::Key::A;sKey = sf::Keyboard::Key::S;dKey = sf::Keyboard::Key::D;
    rClick = sf::Mouse::Button::Right;
    lClick = sf::Mouse::Button::Left;
}

void player::move(float delta, mapa &mapa) {
    dir.x = 0.f; dir.y = 0.f;
    //interaccion teclas
    if(sf::Keyboard::isKeyPressed(wKey) && !sf::Keyboard::isKeyPressed(sKey)) dir.y = -1.f;  
    if(sf::Keyboard::isKeyPressed(aKey) && !sf::Keyboard::isKeyPressed(dKey)) dir.x = -1.f; 
    if(sf::Keyboard::isKeyPressed(sKey) && !sf::Keyboard::isKeyPressed(wKey)) dir.y = 1.f;  
    if(sf::Keyboard::isKeyPressed(dKey) && !sf::Keyboard::isKeyPressed(aKey)) dir.x = 1.f; 

    //speed
    this->speed();
    sf::Vector2f velocity = dir * m_speed * delta;

    // --- COLISIÓN HORIZONTAL ---
    float nextX = m_spr.getPosition().x + velocity.x;
    float sideX;
    if (velocity.x > 0) {sideX = m_width/2;} else {sideX = -m_width/2;}
    
    // Revisamos bordes laterales con un pequeño margen de 1px para no trabarse
    bool chocaArriba = mapa.isSolidAtPixel(nextX + sideX, m_spr.getPosition().y - m_height/2 + 1);
    bool chocaAbajo = mapa.isSolidAtPixel(nextX + sideX, m_spr.getPosition().y + m_height/2 - 1);

    if (!chocaArriba && !chocaAbajo) {
        m_spr.move({velocity.x, 0});
    }

    // --- COLISIÓN VERTICAL ---
    float nextY = m_spr.getPosition().y + velocity.y;
    float sideY;
    if(velocity.y > 0) {sideY = m_height/2;} else {sideY = -m_height/2;}

    bool chocaIzq = mapa.isSolidAtPixel(m_spr.getPosition().x - m_width/2 + 1, nextY + sideY);
    bool chocaDer = mapa.isSolidAtPixel(m_spr.getPosition().x + m_width/2 - 1, nextY + sideY);

    if (!chocaIzq && !chocaDer) {
        m_spr.move({0, velocity.y});
    }

}



void player::texture(){
    if(sf::Keyboard::isKeyPressed(wKey) && !sf::Mouse::isButtonPressed(rClick)) m_spr.setTexture(text2);
    if(sf::Keyboard::isKeyPressed(aKey) && !sf::Mouse::isButtonPressed(rClick)) m_spr.setTexture(text3);
    if(sf::Keyboard::isKeyPressed(sKey) && !sf::Mouse::isButtonPressed(rClick)) m_spr.setTexture(m_txt);
    if(sf::Keyboard::isKeyPressed(dKey) && !sf::Mouse::isButtonPressed(rClick)) m_spr.setTexture(text1);
}

void player::speed(){
    m_speed = 200.f;
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


void player::update(float delta,mapa &mapa) {
    //actualizar player
    this->texture();
    this->move(delta,mapa);
    
    //sf::Vector2f delta1 = dir * m_speed;
    //pl_pos=m_spr.getPosition();
    //m_spr.move(delta1);
    
}

void player::draw(sf::RenderWindow& m_win) {
    m_win.draw(m_spr);
}

void player::updateSkinByMouse(const sf::Vector2f &mouseCoords){
    this->m_mouse(mouseCoords);
}

//posicion del player
sf::Vector2f player::getPosition() const {
    return m_spr.getPosition();
}

sf::FloatRect player::getTheBounds(){
    return m_spr.getGlobalBounds();
}

bool player::attact(sf::RenderWindow &m_win,sf::FloatRect entpos){
    mouse_pos=m_win.mapPixelToCoords(sf::Mouse::getPosition(m_win));
    if(entpos.contains(mouse_pos)){
        if(sf::Mouse::isButtonPressed(lClick)){
            return true;
        }
    }
    return false;
}

int player::manyLife(){
    return corazones;
} 

bool player::isAlive(){
    return vivo;
}

void player::RecieveDamage() {
    this->rDamage = true; // Esto activará la resta de corazones en el siguiente update
}