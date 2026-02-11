#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Mapa.hpp"
#include <SFML/Graphics.hpp>

class entity{
public:
    entity() = default;
    virtual void update(float delta,mapa &mapa) = 0;
    virtual void draw(sf::RenderWindow& m_win) = 0;
    virtual sf::Sprite& getSprite() = 0;

    virtual void updateTexture()=0;
    virtual void drawHitbox(sf::RenderWindow &m_win)=0;
    virtual void syncHitbox()=0;
    virtual void setHitboxes(std::vector<sf::FloatRect> &hitboxes) = 0;
    virtual void colx(sf::FloatRect hitbox) = 0;
    virtual void coly(sf::FloatRect hitbox) = 0;

    virtual void deathDraw() = 0;

    virtual void move(float delta,mapa &mapa) = 0;
    virtual int getHealth() = 0;
    virtual void updateHealth() = 0;
    virtual bool isAlive() = 0;
    virtual const sf::Vector2f attack() = 0;
    virtual void RecieveDamage() = 0;
    virtual sf::FloatRect getHitbox() = 0;
    virtual ~entity() = default;
};

#endif