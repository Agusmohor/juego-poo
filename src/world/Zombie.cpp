#include "world/Zombie.hpp"
#include <cmath>
#include <iostream>

zombie::zombie(const sf::Texture &sprite, const sf::Texture &m_shadow, sf::Vector2f coords) :  entity(sprite,m_shadow) {
    m_spr.setPosition({coords});
    m_speed = 30; color = m_spr.getColor();
    health = 2;
}

void zombie::update(float delta,game &game) {
    prevPos = m_spr.getPosition(); hitboxPrevPos = hitbox.getPosition();
    if (inRaduis() && !isHitting) {move(delta);}
    shadow.setPosition({m_spr.getPosition().x, m_spr.getPosition().y+10});
    updateHealth(); startAttack();
}

void zombie::playAudios(game &game) {
    if (startDamageAudio && !startDeathAudio) {startDamageAudio = false;game.getAudio().playEntityDamaged(); }
    if (startDeathAudio){startDeathAudio = false; game.getAudio().playEntityDead();}
}

void zombie::updateTexture() {
    sf::IntRect rect = m_spr.getTextureRect();

    if (isAlive()) {
        if (ismoving) state = 1;
        if (isHitting) state = 2;
        switch (state) {
            case 0:
                if (rect.position.x >= 160) {
                    rect.position.x = 0;
                }
                m_spr.setTextureRect({{rect.position.x + 32, 0},{txScale}});
                break;
            case 1:
                if (rect.position.x >= 96) {
                    rect.position.x = 0;
                }
                m_spr.setTextureRect({{rect.position.x + 32, 64},{txScale}});
                break;
            case 2:
                if (rect.position.x >= 224) {
                    isHitting = false;
                    rect.position.x = 0;
                }
                if (isHitting) {
                    m_spr.setTextureRect({{rect.position.x + 32, 256},{txScale}});
                    if (m_spr.getTextureRect().position.x >= 128 && m_spr.getTextureRect().position.x <= 160) {damageTime = true;} else {damageTime = false;}
                }
                break;
        }
    }




    damageColor(damaged);
    if (!this->isAlive()) deathDraw();

}

void zombie::draw(sf::RenderWindow &m_win) {
    if (isAlive()) m_win.draw(shadow);
    m_win.draw(m_spr);

}

void zombie::drawHitbox(sf::RenderWindow &m_win) {
    hitbox.setFillColor(sf::Color::Red);
    m_win.draw(hitbox);
}

void zombie::syncHitbox() {
     hitbox.setPosition({m_spr.getPosition().x-6,m_spr.getPosition().y+4});
}

void zombie::colx(const sf::FloatRect& hitbox) {
    if (timer1.getElapsedTime().asSeconds() >= 0.28f) {
        iscolx=false;
        timer1.restart();
    }
    if (this->hitbox.getGlobalBounds().findIntersection(hitbox).has_value()) {
        m_spr.setPosition({prevPos.x,m_spr.getPosition().y});
        this->hitbox.setPosition({hitboxPrevPos.x,this->hitbox.getPosition().y});
        iscolx=true;
    }

}

void zombie::coly(const sf::FloatRect& hitbox) {
    if (timer2.getElapsedTime().asSeconds() >= 0.28f) {
        iscoly=false;
        timer2.restart();
    }
    if (this->hitbox.getGlobalBounds().findIntersection(hitbox).has_value()) {
        m_spr.setPosition({m_spr.getPosition().x,prevPos.y});
        this->hitbox.setPosition({this->hitbox.getPosition().x,hitboxPrevPos.y});
        iscoly=true;
    }

}

void zombie::setHitboxes(std::vector<sf::FloatRect> &hitboxes) {
    this->hitboxes = &hitboxes;
}

void zombie::move(float delta) {
    //diferencia x,y entre el player y la entidad
    dif = pl_pos - m_spr.getPosition();

    //distancia player y entidad
    dist = sqrt(dif.x * dif.x + dif.y * dif.y);
    if (dist != 0.f) { dif /= dist;}
    if (dist > 21){ismoving = true;} else{ismoving = false;}
    if (dif.x < 0){m_spr.setScale({-sprScale.x,sprScale.y});} else{m_spr.setScale(sprScale);}

    //dif seria la "direccion"
    if (timer3.getElapsedTime().asSeconds() >= 0.1f) {
        if(iscolx){
            if(dif.x<0){
            dif={-2,0};
            }else{
            dif={2,0};
            }
        }else if(iscoly){
            if(dif.y<0){
            dif={0,-2};
            }else{
            dif={0,2};
            }
        }
        timer3.restart();
    }

    sf::Vector2f velocity = dif * m_speed *delta;
    m_spr.move(velocity);

    //m_spr.move(dif*m_speed*delta);
    syncHitbox();
    for (auto &box : *hitboxes) {
        colx(box);
    }
    syncHitbox();
    for (auto &box : *hitboxes) {
        coly(box);
    }
    syncHitbox();

    if (dist < 10.6f) ismoving = false;
}

void zombie::getPlyPos(const sf::Vector2f &pl_pos) {
    this->pl_pos = pl_pos;
}

bool zombie::inRaduis() {
    dist2 = (-m_spr.getPosition().x + pl_pos.x) * (-m_spr.getPosition().x + pl_pos.x) + (-m_spr.getPosition().y + pl_pos.y) * (-m_spr.getPosition().y + pl_pos.y);

    if (dist2 > 10*10) {return true;}
    return false;
}

const sf::FloatRect zombie::getGlobalBounds() const {
    return m_spr.getGlobalBounds();
}

void zombie::updateHealth() {
    if (health < 0) health = 0;
    if (health == 0) {vivo = false; state = 1;}
    if (health > 0) {vivo = true; state = 0;}
}

void zombie::recieveDamage() {
    // std::cout << "GOLPE RECIBIDO AL ZOMBIE" << std::endl;
    damaged = true;
    if (health > 0) {
        health--;
        startDamageAudio = true;
    }
}

void zombie::startAttack() {
    if (isHitting && !damage_consumed && damageTime) {
        can_damage = true;
    }else{can_damage = false;}
}

const bool zombie::getHitStatus() const {
    return isHitting;
}

void zombie::setHitStatus(bool status) {
    isHitting = status; if(status) {m_spr.setTextureRect({{0,256},{txScale}}); damage_consumed = false;}
}

bool zombie::canDealDamage() const {
    return can_damage;
}

void zombie::consumeDamage() {
    damage_consumed = true;
}

const sf::Clock& zombie::getHitsCooldown() const {
    return hitsCooldown;
}

void zombie::restartHitsCooldown() {
    hitsCooldown.restart();
}

void zombie::deathDraw() {
    sf::IntRect rect = m_spr.getTextureRect();
    if (state == 1) {startDeathAudio = true; rect.position.x = 0; state = 2; count = 0;}
    if (count < 4) {m_spr.setTextureRect({{rect.position.x + 32,192},{txScale}}); count++;}
    if (count >= 4) {deathOver = true;}
}

void zombie::damageColor(bool cond) {
    if (cond) {
        m_spr.setColor(sf::Color::Red);
        damaged = false;
    }else {
        m_spr.setColor(color);
    }
}

const sf::Vector2f zombie::getPosition() const {
    return m_spr.getPosition();
}

bool zombie::isDeathOver() const {
    return deathOver;
}

bool zombie::killCounted() const {
    return killcount;
}

void zombie::markKillCounted() {
    killcount = true;
}

const zombieSave& zombie::getSaves(){
    saves.x = m_spr.getPosition().x; saves.y = m_spr.getPosition().y;
    return saves;
}


