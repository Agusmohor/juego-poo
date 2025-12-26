#pragma once
#ifndef TREE_HPP
#define TREE_HPP

#include "Player.hpp"
#include <SFML/Window/Mouse.hpp>
#include "Entity.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>

class tree : public entity{
public:
    tree();
    void update(player &m_player);
    void draw(sf::RenderWindow &m_win) override;
private:
    sf::Sprite shape;
    sf::Texture arbol,arbol2;
    sf::Vector2f pl_pos;
    sf::CircleShape radio;
    sf::FloatRect rect;
    sf::Clock timer;
};

#endif