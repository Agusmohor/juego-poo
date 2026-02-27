#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Entity.hpp"
#include "Mapa.hpp"
#include "Tree.hpp"

#include "Abilities.hpp"
#include "Keys.hpp"




class player : public entity{
public:
    player(const sf::Texture &sprite, const sf::Texture &shadow, const sf::Texture& shield,const sf::Texture& fball, bool nuevo);

    void update(float delta,mapa &mapa);
    void draw(sf::RenderWindow &m_win) override;
    void drawShadow(sf::RenderWindow &m_win);
    sf::Sprite& getSprite() override;

    void updateTexture() override;
    const playerSaves& getSaves() ;
    void setSaves(const playerSaves& old_Save);

    void drawHitbox(sf::RenderWindow &m_win) override;
    void syncHitbox() override;
    void setHitboxes(std::vector<sf::FloatRect> &hitboxes) override;

    void colx(const sf::FloatRect hitboxOther) override;
    void coly(const sf::FloatRect hitboxOther) override;

    sf::FloatRect getGlobalBounds() override;
    void updateHealth() override;

    void deathDraw() override;

    bool isAlive() override;
    int getHealth() override;
    int getStamina();
    bool isStaminaEmpty();

    const sf::Vector2f getScale() override;

    void attackSkin();

    void recieveDamage() override;

    void move(float delta,mapa &mapa) override;
    void speed();
    bool cond();

    const bool getHitStatus() const override;
    void setHitStatus(bool status) override;

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
    void startShoot();
    bool getIsShot() const;
    const sf::RectangleShape &getFireball();

    void startHeal();
    void stateHeal();

    bool getDashReady() const;
    void setDashReady(bool ready);
    bool getShieldReady() const;
    void setShieldReady(bool ready);
    bool getFireReady() const;
    void setFireReady(bool ready);
    bool getHealReady() const;
    void setHealReady(bool ready);

    void setKey(const std::array<sf::Keyboard::Scancode,4> &keys);

    const sf::Keyboard::Scancode &getKey(action act) const;


private:
    void updateSaves() ;
    void texture();
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
    sf::Keyboard::Key wKey,aKey,sKey,dKey, shieldKey, dashKey, fireKey, healKey;
    sf::Mouse::Button rClick,lClick;

    float m_width = 30.0f;  // ancho player
    float m_height = 40.0f; //altura player

    //controles
    std::array<sf::Keyboard::Scancode,4> m_keys;

    Abilities abil;

    bool isShieldActive = false;
    sf::Sprite m_shield;
    bool shieldReady = false;

    bool isDashing = false;
    sf::Vector2f dashDir;
    bool dashReady = false;

    sf::Sprite m_fireball;
    sf::RectangleShape fhitbox;
    sf::Vector2f fscale;
    sf::Vector2i fireballScale;
    bool isShot = false;
    bool shotSkin = false;
    sf::Vector2f shootdir;
    bool isShootActive = false;
    bool fireReady = false;

    bool isHealing = false;
    float healRegenTimer = 0.f;
    float healRegenDur = 1.f;
    int c = 4;
    bool healReady = false;
    playerSaves saves;
};

#endif