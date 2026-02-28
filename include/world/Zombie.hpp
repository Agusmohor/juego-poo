#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class zombie : public entity {
    sf::Vector2f dif;
    sf::Color color;
    sf::Clock timer1,timer2,timer3,hitsCooldown;
    bool iscolx=false;
    bool iscoly=false;
    float dist,max_rad,min_rad,dist2;
    bool deathOver = false;
    bool damaged = false; bool doDamage = false;
    bool ismoving=false;
    int count;
    bool killcount = false;

    zombieSave saves;
public:
    zombie(const sf::Texture &m_tex, const sf::Texture &m_shadow, sf::Vector2f coords);

    void update(float delta,mapa &mapa) override;
    void draw(sf::RenderWindow& m_win) override;

    const zombieSave& getSaves();

    void drawHitbox(sf::RenderWindow &m_win) override;
    void syncHitbox() override;
    void setHitboxes(std::vector<sf::FloatRect> &hitboxes) override;
    void coly(const sf::FloatRect hitbox) override;
    void colx(const sf::FloatRect hitbox) override;

    void move(float delta,mapa &mapa) override;
    void updateHealth() override;
    bool isDeathOver();
    void recieveDamage() override;
    const sf::FloatRect getGlobalBounds() const override;
    const sf::Vector2f getPosition() const override;

    void deathDraw() override;

    const sf::Clock& getHitsCooldown();
    void restartHitsCooldown();
    bool const getDamageStatus();
    void setDamageSatus(bool status);

    const bool getHitStatus() const override;
    void setHitStatus(bool status) override;

    void damageColor(bool cond);


    void getPlyPos(const sf::Vector2f &pl_pos);

    void updateTexture() override;

    bool inRaduis();

    bool killCounted();
    void markKillCounted();
};

#endif