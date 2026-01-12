#include "Tree.hpp"

#include <iostream>

tree::tree() : m_spr(t) {
    m_spr.setScale({2,2}); m_spr.setOrigin({4,4});
    m_hitbox.setSize({9,6});
    // m_spr.setTexture(arbol);
    m_spr.setTextureRect({{0,0},{64,64}}); m_spr.setScale({1,1});
    // m_base.setFillColor(sf::Color::Blue);
}

void tree::draw(sf::RenderWindow &m_win) {
    // m_win.draw(m_hitbox);
}

void tree::update() {
    sf::IntRect rect = m_spr.getTextureRect();
    if (rect.position.x  >= 960) {
        rect.position.x = 0;
    }
        rect.position.x += 64;
    m_spr.setTextureRect(rect);
}

void tree::random(const sf::Texture &arbol, const sf::Texture &arbol2, const sf::Texture &arbol3) {
    m_rand = rand()%100;
    // m_rand = 32;
    if (m_rand <= 33) {
        m_spr.setTexture(arbol);
        // m_spr.setTextureRect({{0,0},{64,64}}); m_spr.setScale({1,1});
    }
    if (m_rand > 33 && m_rand < 66) {
        m_spr.setTexture(arbol2);
        // m_spr.setTextureRect({{0,0},{32,32}});
    }
    if (m_rand >= 66) {
        m_spr.setTexture(arbol3);
        // m_spr.setTextureRect({{0,0},{32,32}});
    }
}

void tree::setPos(sf::Vector2f pos) {
    m_spr.setPosition(pos);
    sf::Vector2f basePos = m_spr.getPosition();
    m_hitbox.setPosition({basePos.x+24, basePos.y + 50});
}

sf::FloatRect tree::getHitbox() {
    return m_hitbox.getGlobalBounds();
}

sf::Sprite &tree::getSprite() {
    return m_spr;
}
