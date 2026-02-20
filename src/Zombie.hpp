#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class zombie : public entity {
    sf::Sprite m_spr,shadow;
    sf::RectangleShape hitbox;
    sf::Vector2f pl_pos,dif,m_scale,prevPos,hitboxPrevPos;
    sf::Vector2i scale;
    std::vector<sf::FloatRect>* hitboxes;
    sf::Color color;
    sf::Clock timer1,timer2,timer3,hitsCooldown;
    bool iscolx=false;
    bool iscoly=false;
    float dist,max_rad,min_rad,dist2,m_speed;
    bool vivo=true; bool deathOver = false;
    bool damaged = false; bool isHitting=false; bool doDamage = false;
    bool ismoving=false;
    int health=2;
    int state,count;
public:
    zombie(const sf::Texture &m_tex, const sf::Texture &m_shadow);

    void update(float delta,mapa &mapa) override;
    void draw(sf::RenderWindow& m_win) override;
    sf::Sprite &getSprite() override;

    void drawHitbox(sf::RenderWindow &m_win) override;
    void syncHitbox() override;
    void setHitboxes(std::vector<sf::FloatRect> &hitboxes) override;
    void coly(sf::FloatRect hitbox) override;
    void colx(sf::FloatRect hitbox) override;

    void move(float delta,mapa &mapa) override;
    int getHealth() override;
    void updateHealth() override;
    bool isAlive() override;
    bool isDeathOver();
    const sf::Vector2f getScale() override;
    void recieveDamage() override;
    sf::FloatRect getHitbox() override;

    void deathDraw() override;

    const sf::Clock& getHitsCooldown();
    void restartHitsCooldown();
    bool const getDamageStatus();
    void setDamageSatus(bool status);

    const bool getHitStatus() const override;
    void setHitStatus(bool status) override;

    void damageColor(bool cond);

    sf::Vector2f getPosition();

    void getPlyPos(const sf::Vector2f &pl_pos);

    void updateTexture() override;

    bool inRaduis();
};

#endif