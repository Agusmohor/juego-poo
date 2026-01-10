#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class zombie : public entity {
    sf::Texture m_tex,shadowText;
    sf::Sprite m_spr,shadow;
    sf::RectangleShape hitbox;
    sf::Vector2f pl_pos,dif,scale,prevPos,hitboxPrevPos;
    std::vector<sf::FloatRect> hitboxes;
    float dist,max_rad,min_rad,dist2,m_speed;
    bool vivo=true;
    bool rDamage=false;
    bool ismoving=false;
    int corazones=5;
public:
    zombie();

    void update(float delta,mapa &mapa) override;
    void draw(sf::RenderWindow& m_win) override;
    sf::Sprite &getSprite() override;

    void drawHitbox(sf::RenderWindow &m_win) override;
    void syncHitbox() override;
    void getHitboxes(std::vector<sf::FloatRect> &hitboxes) override;
    void coly(sf::FloatRect hitbox) override;
    void colx(sf::FloatRect hitbox) override;

    void move(float delta,mapa &mapa) override;
    int manyLife() override;
    bool isAlive() override;
    bool attact(sf::RenderWindow &m_win,sf::FloatRect entpos) override;
    void RecieveDamage() override;
    sf::FloatRect getHitbox() override;

    void getPlyPos(const sf::Vector2f &pl_pos);

    void updateTexture() override;

    bool inRaduis();
};

#endif