#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class zombie : public entity {
private:
    // sf::Sprite m_spr;
    // sf::Texture m_tex;
    sf::CircleShape shape;
    sf::Vector2f pl_pos,dir;
public:
    zombie();
    void update() override;
    void draw(sf::RenderWindow& m_win) override;
    void texture() override;
    void move() override;

    void getPlyPos(const sf::Vector2f &pl_pos);
};

#endif