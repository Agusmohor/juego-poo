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
    bool damaged = false;

    bool damageTime = false;
    bool can_damage = false;
    bool damage_consumed = false;
    bool m_damageDeal = false;

    bool ismoving=false;
    int count;
    bool killcount = false;

    bool startDamageAudio = false;
    bool startDeathAudio = false;

    zombieSave saves;

    void move(float delta) override;
    void syncHitbox() override;
    void coly(const sf::FloatRect& hitbox) override;
    void colx(const sf::FloatRect& hitbox) override;
    void updateHealth() override;
    void deathDraw() override;
    void restartHitsCooldown();
    const sf::Clock& getHitsCooldown() const;
    void damageColor(bool cond);
    bool inRaduis();
    void startAttack();
public:
    zombie(const sf::Texture &m_tex, const sf::Texture &m_shadow, sf::Vector2f coords);

    void update(float delta,game& game) override;
    void playAudios(game &game) override;
    void draw(sf::RenderWindow& m_win) override;
    void drawHitbox(sf::RenderWindow &m_win) override;
    void setHitboxes(std::vector<sf::FloatRect> &hitboxes) override;
    void recieveDamage() override;
    const sf::FloatRect getGlobalBounds() const override;
    const sf::Vector2f getPosition() const override;
    void updateTexture() override;
    const bool getHitStatus() const override;
    void setHitStatus(bool status) override;
    const zombieSave& getSaves();
    bool isDeathOver() const;
    void getPlyPos(const sf::Vector2f &pl_pos);
    void markKillCounted();
    bool killCounted() const;

    bool canDealDamage() const;
    void consumeDamage();
};

#endif