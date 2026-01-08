#include "Tree.hpp"

tree::tree() : arbol("../assets/textures/trees/tree1.png"),arbol2("../assets/textures/trees/tree2.png"),arbol3("../assets/textures/trees/tree3.png"),m_spr(arbol) {
    m_spr.setScale({2,2}); m_spr.setOrigin({4,4});
    m_base.setSize({10,6});
    // m_base.setFillColor(sf::Color::Blue);
}

void tree::draw(sf::RenderWindow &m_win) {
    m_win.draw(m_base);
}

void tree::random() {
    m_rand = rand()%100;
    if (m_rand <= 33) m_spr.setTexture(arbol);
    if (m_rand > 33 && m_rand <= 66) m_spr.setTexture(arbol2);
    if (m_rand > 66) m_spr.setTexture(arbol3);
}

void tree::setPos(sf::Vector2f pos) {
    m_spr.setPosition(pos);
    sf::Vector2f basePos = m_spr.getPosition();
    m_base.setPosition({basePos.x+3, basePos.y + 50});
}

sf::FloatRect tree::getHitbox() {
    return m_base.getGlobalBounds();
}

sf::Sprite &tree::getSprite() {
    return m_spr;
}
