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
    float dist,max_rad,min_rad,dist2;
    bool vivo=true;
    bool rDamage=false;
    int corazones=5;
public:
    zombie();
    void update(float delta,mapa &mapa) override;
    void draw(sf::RenderWindow& m_win) override;
    void texture() override;
    void move(float delta,mapa &mapa) override;
    int manyLife() override;
    bool isAlive() override;
    bool attact(sf::RenderWindow &m_win,sf::FloatRect entpos) override;
    void RecieveDamage() override;
    sf::FloatRect getTheBounds() override;

    void getPlyPos(const sf::Vector2f &pl_pos);

    bool inRaduis();
};

#endif