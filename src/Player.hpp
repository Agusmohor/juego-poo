#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Entity.hpp"
#include "Mapa.hpp"
#include "Tree.hpp"

#include "Abilities.hpp"



class player : public entity{
public:
    player(const sf::Texture &sprite, const sf::Texture &shadow);

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
    sf::FloatRect getGlobalBounds() override;
    void updateHealth() override;

    void deathDraw() override;

    bool isAlive() override;
    int getHealth() override;
    int getStamina();
    bool isStaminaEmpty();

    const sf::Vector2f getScale() override;

    void attackSkin();
    void criticSkin();

    void recieveDamage() override;

    void m_mouse(const sf::Vector2f &mouseCoords);
    void move(float delta,mapa &mapa) override;
    void speed();
    bool cond();

    const bool getHitStatus() const override;
    void setHitStatus(bool status) override;

    void updateSkinByMouse(const sf::Vector2f &mouseCoords);
    const sf::Vector2f getPosition() const ;

    //abilities
    void dashMovement();
    void startDash(float dt);
    bool getDashActive();
    void setDashActive(bool active);

    void shield();
    bool getShieldActive();
    void setShieldActive(bool active);

    void shootState(float dt);
    bool getShootActive();
    void setShootActive(bool active);
    void doShoot();
    const sf::CircleShape &getFireball();


private:
    int state;
    sf::Vector2f prevPos, hitboxPrevPos;
    sf::Vector2i scale;

    std::vector<sf::FloatRect>* hitboxes = nullptr;
    sf::RectangleShape hitbox;

    int health = 10;
    int stamina;
    float staminaRegenTimer = 0.f;
    float staminaRegenDur = 0.05f;

    bool isAttacking = false; bool iscritic = false;
    bool isHitting = false;
    float attackTimer = 0.f;
    float attackDur = 0.1f;

    bool vivo = true;
    bool damaged = false;
    bool colision = false;
    bool empty_stamina = false;
    sf::Sprite m_spr,m_shadow;
    float m_speed,dx,dy,m_angle;
    sf::Vector2f pl_pos,dir,mouse_pos,m_scale;
    sf::Keyboard::Key wKey,aKey,sKey,dKey;
    sf::Mouse::Button rClick,lClick;

    float m_width = 30.0f;  // ancho player
    float m_height = 40.0f; //altura player

    Abilities abil;

    bool isShieldActive = false;

    bool isDashing = false;
    sf::Vector2f dashDir;

    sf::CircleShape fireball;
    bool isShot = false;
    sf::Vector2f shootdir;
    bool isShootActive = false;
};

#endif