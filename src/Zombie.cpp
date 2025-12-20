#include "Zombie.h"
#include <cmath>

zombie::zombie() : m_tex("../assets/textures/prueba.png"), m_spr(m_tex) {
    m_spr.setScale(sf::Vector2f(5.f,5.f));
    m_spr.setPosition({100.f, 100.f});
}

void zombie::update() {
    if (this->inRaduis()) {this->move();}
}

void zombie::draw(sf::RenderWindow &m_win) {
    m_win.draw(m_spr);
}

void zombie::texture() {

}

void zombie::move() {
    dir.x = 0.f; dir.y = 0.f;
    if (pl_pos.x >= m_spr.getPosition().x) {dir.x = 1.f;} else {dir.x = -1.f;}
    if (pl_pos.y >= m_spr.getPosition().y) {dir.y = 1.f;} else {dir.y = -1.f;}
   m_spr.move(dir);
}

void zombie::getPlyPos(const sf::Vector2f &pl_pos) {
    this->pl_pos = pl_pos;
}

bool zombie::inRaduis() {
    dist = sqrt((m_spr.getPosition().x - pl_pos.x) * (m_spr.getPosition().x - pl_pos.x) + (m_spr.getPosition().y - pl_pos.y) * (m_spr.getPosition().y - pl_pos.y));

    if (dist < 600 && dist > 20) {return true;}
    return false;
}