#include "Zombie.h"
#include <cmath>
#include <iostream>

zombie::zombie() : m_tex("../assets/textures/entity/zombie/sprite.png"), m_spr(m_tex) {
    scale = sf::Vector2f(0.6,0.6); m_spr.setScale(scale);
    m_spr.setTextureRect({{0,0},{32,32}}); m_spr.setOrigin({16,16});
    m_spr.setPosition({100.f, 100.f}); m_speed = 40;
}

void zombie::update(float delta,mapa &mapa) {
    if (this->inRaduis()) {this->move(delta,mapa);}
    if(corazones!=0){
        if(rDamage){
            corazones--;
            rDamage=false;
        }
    }else{
        vivo=false;
    }
    // std::cout<<corazones<<std::endl;
}

void zombie::updateTexture() {
    sf::IntRect rect = m_spr.getTextureRect();
    if (ismoving) {
        if (rect.position.x >= 96) {
            rect.position.x = 0;
        }
        m_spr.setTextureRect({{rect.position.x + 32, 64},{32,32}});
    }else {
        if (rect.position.x >= 160) {
            rect.position.x = 0;
        }
        m_spr.setTextureRect({{rect.position.x + 32, 0},{32,32}});
    }
}

void zombie::draw(sf::RenderWindow &m_win) {
    m_win.draw(m_spr);
}

sf::Sprite &zombie::getSprite() { return m_spr;}

void zombie::texture() {

}

void zombie::move(float delta,mapa &mapa) {
    //diferencia x,y entre el player y la entidad
    dif = pl_pos - m_spr.getPosition();

    //distancia player y entidad
    dist = sqrt(dif.x * dif.x + dif.y * dif.y);
    if (dist != 0.f) { dif /= dist;}
    if (dist > 21){ismoving = true;} else{ismoving = false;}
    // std::cout << dist << std::endl;
    //{1,-1}
    //dif seria la "direccion"
    m_spr.move(dif*m_speed*delta);
}

void zombie::getPlyPos(const sf::Vector2f &pl_pos) {
    this->pl_pos = pl_pos;
}

bool zombie::inRaduis() {
    dist2 = (m_spr.getPosition().x - pl_pos.x) * (m_spr.getPosition().x - pl_pos.x) + (m_spr.getPosition().y - pl_pos.y) * (m_spr.getPosition().y - pl_pos.y);

    if (dist2 < 600*600 && dist2 > 20*20) {return true;}
    return false;
}

sf::FloatRect zombie::getHitbox(){
    return m_spr.getGlobalBounds();
}

bool zombie::attact(sf::RenderWindow &m_win,sf::FloatRect entpos){
    return true;
}

int zombie::manyLife(){
    return corazones;
} 

bool zombie::isAlive(){
    return vivo;
}

void zombie::RecieveDamage() {
    std::cout << "GOLPE RECIBIDO AL ZOMBIE" << std::endl;
    this->rDamage = true; // Esto activará la resta de corazones en el siguiente update
}