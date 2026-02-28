#include "world/Player.hpp"
#include <cmath>
#include "world/Mapa.hpp"
#include "world/Tree.hpp"
#include <iostream>
#include <signal.h>


player::player(const sf::Texture &sprite,const sf::Texture &sha_tex,const sf::Texture& shield, const sf::Texture& fball) :  entity(sprite,sha_tex),stamina(180), m_shield(shield), m_fireball(fball) {
    fireballScale = sf::Vector2i(16,10); m_fireball.setTextureRect({{0,0},{fireballScale}});
    m_fireball.setScale(sprScale);
    m_shield.setOrigin({16,16}); m_fireball.setOrigin({8,5});
    m_spr.setPosition({1120,1184});
    wKey = sf::Keyboard::Key::W;aKey = sf::Keyboard::Key::A;sKey = sf::Keyboard::Key::S;dKey = sf::Keyboard::Key::D;
    lClick = sf::Mouse::Button::Left;
    fhitbox.setFillColor(sf::Color::Red);
    fhitbox.setSize({4,4}); fhitbox.setOrigin({2,2});
    health = 10;
}

void player::move(float delta) {
    dir.x = 0.f; dir.y = 0.f;
    //interaccion teclas
    if(sf::Keyboard::isKeyPressed(wKey) && !sf::Keyboard::isKeyPressed(sKey)) {
        dir.y = -1.f;
    }
    if(sf::Keyboard::isKeyPressed(sKey) && !sf::Keyboard::isKeyPressed(wKey)) {
        dir.y = 1.f;
    }
    if(sf::Keyboard::isKeyPressed(dKey) && !sf::Keyboard::isKeyPressed(aKey)) {
        dir.x = 1.f; m_spr.setScale(sprScale);
    }
    if(sf::Keyboard::isKeyPressed(aKey) && !sf::Keyboard::isKeyPressed(dKey)) {
        dir.x = -1.f; m_spr.setScale({-sprScale.x,sprScale.y});
    }

    //normalizar direccion
    if (dir.x != 0 && dir.y != 0) {
        float length = sqrt(dir.x*dir.x + dir.y*dir.y);
        dir /= length;
    }
    //speed
    speed();
    sf::Vector2f velocity = dir * m_speed *delta;
    prevPos = m_spr.getPosition();

    m_spr.move({velocity.x,0.f});
    syncHitbox();
    for (auto& box : *hitboxes) colx(box);

    m_spr.move({0.f,velocity.y});
    syncHitbox();
    for (auto& box : *hitboxes) coly(box);


}



void player::texture(){
    if ((sf::Keyboard::isKeyPressed(wKey) || sf::Keyboard::isKeyPressed(aKey) || sf::Keyboard::isKeyPressed(sKey) || sf::Keyboard::isKeyPressed(dKey) )) {
         state = 1;
    }else {
         state = 0;
    }


}

void player::updateTexture() {
    sf::IntRect rect = m_spr.getTextureRect();
    if (isAttacking) state = 5;
    if (isDashing) state = 7;
    switch (state) {
        case 0:
            if (rect.position.x >= 192) {
                rect.position.x = 0;
            }
            m_spr.setTextureRect({{rect.position.x + 32, 0},{txScale}});
            break;
        case 1:
            if (rect.position.x >= 96) {
                rect.position.x = 0;
            }
            m_spr.setTextureRect({{rect.position.x + 32, 65},{txScale}});
            break;
        case 2:
            if (rect.position.x >= 224) {
                rect.position.x = 0;
            }
            m_spr.setTextureRect({{rect.position.x + 32,97},{txScale}});
            break;
        case 5:
            if (rect.position.x >= 160) {
                isAttacking = false; isHitting = false;
                rect.position.x = 0;
            }
            if (isAttacking) {
                m_spr.setTextureRect({{rect.position.x + 32,289},{txScale}});
            }
            break;
        case 7:
            if (rect.position.x >= 64) {
                rect.position.x = 0;
            }
            if (isDashing) {
                m_spr.setTextureRect({{rect.position.x + 32, 321},{txScale}});
            }
            break;

    }
    if (!isAlive()) deathDraw();
    sf::Vector2f fdir = shootdir;
    float len = std::sqrt(fdir.x*fdir.x + fdir.y*fdir.y); if (len != 0.f) fdir /= len;
    float ang = std::atan2(fdir.y,fdir.x); m_fireball.setRotation(sf::radians(ang));

    if (m_fireball.getTextureRect().position.x >= 80){m_fireball.setTextureRect({{0,0},{fireballScale}});}
    m_fireball.setTextureRect({{m_fireball.getTextureRect().position.x +16,0},{fireballScale}});
}

void player::speed(){
    m_speed = 50;
    if (staminaRegenTimer >= staminaRegenDur) {
        if(stamina < 180){
            stamina++;
        }
        staminaRegenTimer = 0.f;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && stamina > 0 && this->cond() && !empty_stamina){
        stamina--; m_speed *= 1.2; state = 2;
    }

    if (stamina == 0) empty_stamina = true;
    if (stamina == 180) empty_stamina = false;
}

bool player::cond(){
    if(sf::Keyboard::isKeyPressed(wKey)) return true;
    if(sf::Keyboard::isKeyPressed(aKey)) return true;
    if(sf::Keyboard::isKeyPressed(sKey)) return true;
    if(sf::Keyboard::isKeyPressed(dKey)) return true;

    return false;
}

void player::update(float delta, game& game) {
    //audios
    if (startDashAudio){startDashAudio = false; game.getAudio().playDash(); }

    prevPos = m_spr.getPosition(); hitboxPrevPos = hitbox.getPosition();
    //actualizar player
    texture();
    staminaRegenTimer += delta;
    healRegenTimer += delta;
    if (!isAttacking && !isDashing) { move(delta);}

    // std::cout << health << std::endl;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) health--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) health++;
    updateHealth();

    //sf::Vector2f delta1 = dir * m_speed;
    //pl_pos=m_spr.getPosition();
    //m_spr.move(delta1);
    attackTimer += delta;
    if (attackTimer >= attackDur) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ) { attackSkin();}
        attackTimer = 0.f;
    }

    abil.update(delta,*this);
    shadow.setPosition({m_spr.getPosition().x, m_spr.getPosition().y+10});
    m_shield.setPosition({m_spr.getPosition().x, m_spr.getPosition().y});

}

void player::draw(sf::RenderWindow& m_win) {
    if(isShot){m_win.draw(m_fireball);}
    if (state != 4) m_win.draw(shadow);
    m_win.draw(m_spr);
    if (isShieldActive){m_win.draw(m_shield);}
    // m_win.draw(fhitbox);
}

//posicion del player
const sf::Vector2f player::getPosition() const {
    return m_spr.getPosition();
}

const sf::FloatRect player::getGlobalBounds() const {
    return m_spr.getGlobalBounds();
}

const bool player::getHitStatus() const {return isHitting;}
void player::setHitStatus(bool status) {isHitting = status;}

void player::attackSkin(){
    if (!isAttacking) {
        state = 5; isAttacking = true; isHitting = true;
        m_spr.setTextureRect({{0,289},{txScale}});
    }
}


int player::getStamina() const {
    return stamina;
}

bool player::isStaminaEmpty() const {
    return empty_stamina;
}

void player::recieveDamage() {
    if (!isShieldActive) health--;
}


void player::colx(const sf::FloatRect& hitboxOther) {
    if (this->hitbox.getGlobalBounds().findIntersection(hitboxOther).has_value()) {
        m_spr.setPosition({prevPos.x,m_spr.getPosition().y});
        syncHitbox();
    }
}

void player::coly(const sf::FloatRect& hitboxOther) {
    if (this->hitbox.getGlobalBounds().findIntersection(hitboxOther).has_value()) {
        m_spr.setPosition({m_spr.getPosition().x,prevPos.y});
        syncHitbox();
    }
}

void player::setHitboxes(std::vector<sf::FloatRect> &hitboxes) {
    this->hitboxes = &hitboxes;
}

void player::drawHitbox(sf::RenderWindow &m_win) {
    m_win.draw(hitbox);
}

void player::syncHitbox() {
    hitbox.setPosition({m_spr.getPosition().x-6,m_spr.getPosition().y+4});
}

void player::updateHealth() {
    if (health <= 0) {
        health = 0;vivo = false;
        if (state != 4){state = 3;}
    }
    else {vivo = true;}

    if (health >= 14) health = 14;

}

void player::deathDraw() {
    sf::IntRect rect = m_spr.getTextureRect();
    if (state == 3) rect.position.x = 0; state = 4;
    m_spr.setTextureRect({{rect.position.x + 32,192},{txScale}});

}

//abilidades
void player::dashMovement() {
    startDashAudio = true;
    m_spr.setTextureRect({{0,321},{txScale}});
    isDashing = true;
    if (dir != sf::Vector2f(0,0)) {
        float length = sqrt(dir.x*dir.x + dir.y*dir.y);
        if (length != 0) dir /= length;
        dashDir = dir;
    }else {
        if (getScale().x < 0) {
            dashDir = sf::Vector2f(-1,0);
        }else {
            dashDir = sf::Vector2f(1,0);
        }
    }
}

void player::startDash(float dt) {
    float dashSpeed = 400.f;
    m_spr.move(dashDir * dashSpeed * dt);
}

bool player::getDashActive() const {
    return isDashing;
}

void player::setDashActive(bool active) {
    isDashing = active;
}

bool player::getDashReady() const {return dashReady;}
void player::setDashReady(bool ready) {dashReady = ready;}

void player::shield() {
    isShieldActive = true;
}

bool player::getShieldActive() const {
    return isShieldActive;
}

void player::setShieldActive(bool active) {
    isShieldActive = active;
}

bool player::getShieldReady() const {return shieldReady;}
void player::setShieldReady(bool ready) {shieldReady = ready;}

void player::setShootActive(bool active){
    isShootActive = active;
}

bool player::getShootActive() const {
    return isShootActive;
}

void player::shootState(float dt){
    if (!isShot && isShootActive) {
        m_fireball.setPosition(getPosition());
        isShot = true;
    }
    if (isShot) {
        if (shootdir != sf::Vector2f(0,0)) {
            // m_fireball.setScale({shootdir});
        }else {
            if (m_spr.getScale().x < 0) {
                shootdir = sf::Vector2f(-1,0);
            }else {
                shootdir = sf::Vector2f(1,0);
            }
        }
        float fspeed = 100;
        m_fireball.move(shootdir * dt * fspeed);

        sf::Vector2f distfire = getPosition() - m_fireball.getPosition();
        if (std::abs(distfire.x) > 40 || std::abs(distfire.y) > 40) { 
            isShot = false; m_fireball.setPosition({-10000,-10000});
        }
    }
    fhitbox.setPosition(m_fireball.getPosition());
}

void player::startShoot(){
    isShootActive = true;
    shootdir = dir;
    shotSkin = true;
}

bool player::getIsShot() const {return isShot;}

const sf::RectangleShape& player::getFireball() const {
    return fhitbox;
}

bool player::getFireReady() const {return fireReady;}
void player::setFireReady(bool ready) {fireReady = ready;}


void player::stateHeal(){
    if(isHealing) {
        if(healRegenTimer >= healRegenDur) {
            if(health < 14) {
                health++;
                c -= 1;
                // std::cout << "Curado! Vida actual: " << health << std::endl;
            }
            healRegenTimer = 0.f; 
        
        }
        if(c<=0 || health >= 14){
            isHealing = false;
            c = 4;
        }
    }
}

void player::startHeal(){
    isHealing = true;
}

bool player::getHealReady() const {return healReady;}
void player::setHealReady(bool ready) {healReady = ready;}

//keys
void player::setKey(const std::array<sf::Keyboard::Scancode,4>& keys) {
    m_keys = keys;
}

const sf::Keyboard::Scancode& player::getKey(action act) const {
    return m_keys[static_cast<int>(act)];
}

//obtener stats
const playerSaves& player::getSaves() {
    updateSaves();
    return saves;
}

void player::updateSaves() {
    saves.health = health; saves.stam = stamina;
    saves.x = m_spr.getPosition().x; saves.y = m_spr.getPosition().y;
}

void player::setSaves(const playerSaves &old_Save) {
    playerSaves ps;
    if (ps == old_Save) {
        return;
    }else {
        health = old_Save.health; stamina = old_Save.stam;
        m_spr.setPosition({old_Save.x,old_Save.y});
    }

}
