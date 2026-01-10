#pragma once
#ifndef TREE_HPP
#define TREE_HPP

#include "Entity.hpp"
#include <SFML/Graphics/CircleShape.hpp>

class tree {
public:
    tree();

    void update();
    void draw(sf::RenderWindow &m_win);

    void setPos(sf::Vector2f pos);

    sf::FloatRect getHitbox();

    void random();

    sf::Sprite& getSprite() ;

private:
    int m_rand;
    sf::Texture arbol,arbol2,arbol3;
    sf::Sprite m_spr;
    sf::RectangleShape m_hitbox;


};

#endif