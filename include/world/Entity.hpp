#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "core/Game.hpp"

#include "core/Drawble.hpp"
#include "gameplay/Stats.hpp"

class entity : public drawble {
protected:
    sf::Sprite m_spr,shadow;
    int state,health = 10;
    float m_speed;
    sf::Vector2i txScale;
    sf::RectangleShape hitbox;
    std::vector<sf::FloatRect>* hitboxes;
    sf::Vector2f sprScale, pl_pos, prevPos, hitboxPrevPos;
    sf::Color color;
    bool vivo = true;
    bool isHitting = false;
    bool damaged = false;

    //audio
    bool startSwordAudio = false;

    virtual void damageColor(bool cond) { if (cond) {m_spr.setColor(sf::Color::Red); damaged = false;}else{m_spr.setColor(color);}}
public:
    entity(const sf::Texture& spr_tex,const sf::Texture& sha_tex) : m_spr(spr_tex), shadow(sha_tex) {
        sprScale = sf::Vector2f(0.6,0.6); m_spr.setScale(sprScale); shadow.setScale(sprScale);
        txScale = sf::Vector2i(32,32); m_spr.setOrigin({16,16}); shadow.setOrigin({9,3});
        m_spr.setTextureRect({{0,0},{txScale}});
        hitbox.setSize({10,3}); hitbox.setPosition({m_spr.getPosition().x-6,m_spr.getPosition().y+4}); hitbox.setFillColor(sf::Color::Blue);
        color = m_spr.getColor();
    }

    virtual void update(float delta,game &game) = 0;
    virtual void playAudios(game& game){};

    virtual void updateTexture()=0;
    virtual void drawHitbox(sf::RenderWindow &m_win)=0;
    virtual void syncHitbox() = 0;
    virtual void setHitboxes(std::vector<sf::FloatRect> &hitboxes) = 0;
    virtual void colx(const sf::FloatRect& hitbox) = 0;
    virtual void coly(const sf::FloatRect& hitbox) = 0;

    virtual void deathDraw() = 0;

    virtual void move(float delta) = 0;
    virtual int getHealth() const {return health;};
    virtual void updateHealth() = 0;
    virtual bool isAlive() const {return vivo;};
    virtual const sf::Vector2f getScale() const {return m_spr.getScale();};

    virtual const bool getHitStatus() const {return isHitting;};
    virtual void setHitStatus(bool status) {};

    virtual void recieveDamage() {};
    virtual void recieveDamage(int i) {};

    virtual ~entity() = default;
};

#endif