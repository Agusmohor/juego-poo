#include "Zombie.h"

zombie::zombie() : shape(30,30) {
    shape.setFillColor(sf::Color::Red);
    shape.setPosition({100.f, 100.f});
}

void zombie::update() {
    this->move();
}

void zombie::draw(sf::RenderWindow &m_win) {
    m_win.draw(shape);
}

void zombie::texture() {

}

void zombie::move() {
    dir.x = 0.f; dir.y = 0.f;
    if (pl_pos.x > shape.getPosition().x) {dir.x = 1.f;} else {dir.x = -1.f;}
    if (pl_pos.y > shape.getPosition().y) {dir.y = 1.f;} else {dir.y = -1.f;}
   shape.move(dir);
}

void zombie::getPlyPos(const sf::Vector2f &pl_pos) {
    this->pl_pos = pl_pos;
}
