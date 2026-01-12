#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Entity.hpp"
#include "Mapa.hpp"
#include "Tree.hpp"


class player : public entity{
public:
    player();

    void update(float delta,mapa &mapa);
    void draw(sf::RenderWindow &m_win) override;
    sf::Sprite& getSprite() override;

    void updateTexture() override;

    void drawHitbox(sf::RenderWindow &m_win) override;
    void syncHitbox() override;
    void setHitboxes(std::vector<sf::FloatRect> &hitboxes) override;

    void colx(sf::FloatRect hitbox) override;
    void coly(sf::FloatRect hitbox) override;

    void texture();
    sf::FloatRect getHitbox() override;
    void updateHealth() override;

    void deathDraw() override;

    bool isAlive() override;
    int getHealth() override;
    bool attact(sf::RenderWindow &m_win,sf::FloatRect entpos) override;
    void RecieveDamage() override;

    void m_mouse(const sf::Vector2f &mouseCoords);
    void move(float delta,mapa &mapa) override;
    void speed();
    bool cond();


    void updateSkinByMouse(const sf::Vector2f &mouseCoords);
    sf::Vector2f getPosition() const ;





private:
    int state;
    sf::Clock time;
    sf::Vector2f prevPos, hitboxPrevPos;
    sf::Vector2i scale;

    std::vector<sf::FloatRect> hitboxes;
    sf::RectangleShape hitbox;

    int health = 10;

    bool vivo = true;
    bool rDamage = false;
    bool colision = false;
    sf::Texture sprite,shadow;
    sf::Sprite m_spr,m_shadow;
    float m_speed,dx,dy,m_angle; int stamina;
    sf::Vector2f pl_pos,dir,mouse_pos,m_scale;
    sf::Keyboard::Key wKey,aKey,sKey,dKey;
    sf::Mouse::Button rClick,lClick;

    float m_width = 30.0f;  // ancho player
    float m_height = 40.0f; //altura player
};

#endif