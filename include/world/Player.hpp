#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Entity.hpp"
#include "Mapa.hpp"
#include "Tree.hpp"

#include "gameplay/Abilities.hpp"
#include "core/Keys.hpp"


class player : public entity {
    int stamina;
    float staminaRegenTimer = 0.f;
    float staminaRegenDur = 0.05f;

    bool isAttacking = false;
    float attackTimer = 0.f;
    float attackDur = 0.1f;

    bool empty_stamina = false;
    sf::Vector2f dir;
    sf::Keyboard::Key wKey,aKey,sKey,dKey, shieldKey, dashKey, fireKey, healKey;
    sf::Mouse::Button lClick;

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

    //audio
    bool startDashAudio = false;
    bool startFireAudio = false;
    bool startHealAudio = false;
    bool startShieldAudio = false;
    bool finishShieldAudio = false;

    void move(float delta) override;
    void syncHitbox() override;
    void colx(const sf::FloatRect& hitboxOther) override;
    void coly(const sf::FloatRect& hitboxOther) override;
    void updateHealth() override;
    void deathDraw() override;

    void updateSaves();
    void texture();
    void attackSkin();
    void speed();
    bool cond();

public:
    player(const sf::Texture &sprite, const sf::Texture &shadow, const sf::Texture& shield,const sf::Texture& fball);

    void update(float delta,game& game) override;
    void draw(sf::RenderWindow &m_win) override;
    void updateTexture() override;
    void drawHitbox(sf::RenderWindow &m_win) override;
    void setHitboxes(std::vector<sf::FloatRect> &hitboxes) override;
    const sf::Vector2f getPosition() const override;
    const sf::FloatRect getGlobalBounds() const override;
    void recieveDamage() override;
    const bool getHitStatus() const override;
    void setHitStatus(bool status) override;

    const playerSaves& getSaves();
    void setSaves(const playerSaves& old_Save);
    int getStamina() const;
    bool isStaminaEmpty() const;

    //abilities
    void dashMovement();
    void startDash(float dt);
    bool getDashActive() const;
    void setDashActive(bool active);

    void shield();
    bool getShieldActive() const;
    void setShieldActive(bool active);

    void shootState(float dt);
    bool getShootActive() const;
    void setShootActive(bool active);
    void startShoot();
    bool getIsShot() const;
    const sf::RectangleShape &getFireball() const;

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

};

#endif