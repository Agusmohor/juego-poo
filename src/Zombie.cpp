#include "Zombie.h"
#include <cmath>
#include <iostream>

zombie::zombie() : m_tex("../assets/textures/prueba.png"), m_spr(m_tex) {
    // m_spr.setScale(sf::Vector2f(5.f,5.f));
    m_spr.setPosition({100.f, 100.f});
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
    if (dist != 0.f) { dif /= dist; }
    //{1,-1}
    //dif seria la "direccion"
    m_spr.move(dif*120.f*delta);
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