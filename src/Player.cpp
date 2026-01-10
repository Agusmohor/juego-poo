#include "Player.hpp"
#include <cmath>
#include "Mapa.hpp"
#include <iostream>

player::player() : still("../assets/textures/prueba.png"),walk("../assets/textures/derecha.png"), run("../assets/textures/izq.png"), text3("../assets/textures/abajoizq.png"), m_spr(still),m_speed(5),stamina(200){
    if(!still.loadFromFile("../assets/textures/prueba.png")) throw std::runtime_error("err");
    // m_spr.setScale({1,1});
    m_spr.setOrigin({8,8}); m_spr.setPosition({80,80});
    dir.x = 0.f; dir.y = 0.f;
    wKey = sf::Keyboard::Key::W;aKey = sf::Keyboard::Key::A;sKey = sf::Keyboard::Key::S;dKey = sf::Keyboard::Key::D;
    rClick = sf::Mouse::Button::Right;
    lClick = sf::Mouse::Button::Left;
    hitbox.setSize({10,3}); hitbox.setPosition({m_spr.getPosition().x-6,m_spr.getPosition().y+2}); hitbox.setFillColor(sf::Color::Blue);
}

void player::move(float delta, mapa &mapa) {
    dir.x = 0.f; dir.y = 0.f;
    //interaccion teclas
    if (!colision) {
        if(sf::Keyboard::isKeyPressed(wKey) && !sf::Keyboard::isKeyPressed(sKey)) dir.y = -1.f;
        if(sf::Keyboard::isKeyPressed(aKey) && !sf::Keyboard::isKeyPressed(dKey)) dir.x = -1.f;
        if(sf::Keyboard::isKeyPressed(sKey) && !sf::Keyboard::isKeyPressed(wKey)) dir.y = 1.f;
        if(sf::Keyboard::isKeyPressed(dKey) && !sf::Keyboard::isKeyPressed(aKey)) dir.x = 1.f;
    }

    //speed
    this->speed();
    sf::Vector2f velocity = dir * m_speed * delta;
    prevPos = m_spr.getPosition(); this->syncHitbox();
    sf::FloatRect hb = hitbox.getGlobalBounds();

    float dx = velocity.x;
    if (dx != 0.f)
    {
        float probeX = (dx > 0.f) ? (hb.position.x + hb.size.x + dx + 10.f) : (hb.position.x + dx - 10.f);
        bool top    = mapa.isSolidAtPixel(probeX, hb.position.y + 10.f);
        bool midx    = mapa.isSolidAtPixel(probeX,hb.position.y + hb.size.y * 0.5f);
        bool bottom = mapa.isSolidAtPixel(probeX, hb.position.y + hb.size.y - 8.f);
        if (!top && !bottom && !midx)
            m_spr.move({dx, 0.f});
    }

    this->syncHitbox();
    for (auto& box : hitboxes) colx(box.getHitbox());

    hb = hitbox.getGlobalBounds();
    float dy = velocity.y;
    if (dy != 0.f)
    {
        float probeY = (dy > 0.f) ? (hb.position.y + hb.size.y + dy + 24.f) : (hb.position.y + dy - 5.f);
        bool left  = mapa.isSolidAtPixel(hb.position.x + 10.f, probeY);
        bool midy = mapa.isSolidAtPixel(hb.position.x + hb.size.x * 0.8f, probeY);
        bool right = mapa.isSolidAtPixel(hb.position.x + hb.size.x - 10.f, probeY);
        if (!left && !right && !midy)
            m_spr.move({0.f, dy});
    }

    this->syncHitbox();
    for (auto& box : hitboxes) coly(box.getHitbox());

}



void player::texture(){
    if(sf::Keyboard::isKeyPressed(wKey) && !sf::Mouse::isButtonPressed(rClick)) m_spr.setTexture(run);
    if(sf::Keyboard::isKeyPressed(aKey) && !sf::Mouse::isButtonPressed(rClick)) m_spr.setTexture(text3);
    if(sf::Keyboard::isKeyPressed(sKey) && !sf::Mouse::isButtonPressed(rClick)) m_spr.setTexture(still);
    if(sf::Keyboard::isKeyPressed(dKey) && !sf::Mouse::isButtonPressed(rClick)) m_spr.setTexture(walk);
}

void player::speed(){
    m_speed = 100;
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
    if(m_angle < 0 && m_angle > -90) m_spr.setTexture(walk);
    if(m_angle <= -90 && m_angle >= -180) m_spr.setTexture(run);
    if(m_angle > 90 && m_angle < 180) m_spr.setTexture(text3);
    if(m_angle <= 90 && m_angle >= 0) m_spr.setTexture(still);
        
    // std::cout << "ang " << m_angle << " dx " << dx<< " dy " << dy << " posmouse " << mouseCoords.x << " x "<< mouseCoords.y << " y "<<std::endl;
    // std::cout << mouseCoords.x << " " << mouseCoords.y <<std::endl;aW
}


void player::update(float delta,mapa &mapa) {
    prevPos = m_spr.getPosition(); hitboxPrevPos = hitbox.getPosition();

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

sf::FloatRect player::getHitbox(){
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

sf::Sprite &player::getSprite(){ return m_spr; }


void player::colx(sf::FloatRect other_hitbox) {
    if (hitbox.getGlobalBounds().findIntersection(other_hitbox).has_value()) {
        m_spr.setPosition({prevPos.x,m_spr.getPosition().y});
        hitbox.setPosition({hitboxPrevPos.x,hitbox.getPosition().y});
    }

}

void player::coly(sf::FloatRect other_hitbox) {
    if (hitbox.getGlobalBounds().findIntersection(other_hitbox).has_value()) {
        m_spr.setPosition({m_spr.getPosition().x,prevPos.y});
        hitbox.setPosition({hitbox.getPosition().x,hitboxPrevPos.y});
    }
}

void player::getHitboxes(std::vector<tree> &hitboxes) {
    this->hitboxes = hitboxes;
}

void player::drawHitbox(sf::RenderWindow &m_win) {
    m_win.draw(hitbox);
}

void player::syncHitbox() {
    hitbox.setPosition({m_spr.getPosition().x-6,m_spr.getPosition().y+2});
}