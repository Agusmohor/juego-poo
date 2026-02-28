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
    treeSave getSaves() const override;
    void setPos(sf::Vector2f pos) override;

    const sf::Vector2f getPosition() const override;
    const sf::FloatRect getGlobalBounds() const override;

    sf::FloatRect getHitbox() override;

    void random(const sf::Texture &arbol, const sf::Texture &arbol2, const sf::Texture &arbol3) override;

private:
    int m_rand;


};

#endif