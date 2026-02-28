#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Mapa.hpp"
#include <SFML/Graphics.hpp>

#include "core/Drawble.h"
#include "gameplay/Stats.hpp"

class entity : public drawble {
protected:
    sf::Sprite m_spr,shadow;
    int state,health;
    sf::Vector2f sprScale;
    sf::Vector2i txScale;
    sf::RectangleShape hitbox;
public:
    entity(const sf::Texture& spr_tex,const sf::Texture& sha_tex) : m_spr(spr_tex), shadow(sha_tex) {
        sprScale = sf::Vector2f(0.6,0.6); m_spr.setScale(sprScale); shadow.setScale(sprScale);
        txScale = sf::Vector2i(32,32); m_spr.setOrigin({16,16}); shadow.setOrigin({9,3});
        m_spr.setTextureRect({{0,0},{txScale}});
        hitbox.setSize({10,3}); hitbox.setPosition({m_spr.getPosition().x-6,m_spr.getPosition().y+4}); hitbox.setFillColor(sf::Color::Blue);
    }
    virtual void update(float delta,mapa &mapa) = 0;
    virtual void draw(sf::RenderWindow& m_win) = 0;

    virtual void updateTexture()=0;
    virtual void drawHitbox(sf::RenderWindow &m_win)=0;
    virtual void syncHitbox() = 0;
    virtual void setHitboxes(std::vector<sf::FloatRect> &hitboxes) = 0;
    virtual void colx(const sf::FloatRect hitbox) = 0;
    virtual void coly(const sf::FloatRect hitbox) = 0;

    virtual void deathDraw() = 0;

    virtual void move(float delta,mapa &mapa) = 0;
    virtual int getHealth() = 0;
    virtual void updateHealth() = 0;
    virtual bool isAlive() = 0;
    virtual const sf::Vector2f getScale() = 0;

    virtual const bool getHitStatus() const = 0;
    virtual void setHitStatus(bool status) = 0;

    virtual void recieveDamage() = 0;

    virtual ~entity() = default;
};

#endif