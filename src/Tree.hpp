#pragma once
#ifndef TREE_HPP
#define TREE_HPP

#include "Entity.hpp"
#include <SFML/Graphics/CircleShape.hpp>

#include "obstacle.hpp"

class tree : public obstacle{
public:
    tree(sf::Vector2f coords);

    void update() override;
    void draw(sf::RenderWindow &m_win) override;
    const treeSave& getSaves() override;
    void setPos(sf::Vector2f pos) override;
    sf::Vector2f getPosition() override;

    sf::FloatRect getHitbox() override;

    void random(const sf::Texture &arbol, const sf::Texture &arbol2, const sf::Texture &arbol3) override;

    sf::Sprite& getSprite() override;

private:
    int m_rand;
    sf::Texture t;
    sf::Sprite m_spr;
    sf::RectangleShape m_hitbox;

    treeSave saves;

};

#endif