#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class zombie : public entity {
private:
    sf::Texture m_tex;
    sf::Sprite m_spr;
    // sf::CircleShape shape;
    sf::Vector2f pl_pos,dif;
    float dist,rad;
public:
    zombie();
    void update() override;
    void draw(sf::RenderWindow& m_win) override;
    void texture() override;
    void move() override;

    void getPlyPos(const sf::Vector2f &pl_pos);

    bool inRaduis();
};

#endif