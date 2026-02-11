#include "Zombie.hpp"
#include <cmath>
#include <iostream>

zombie::zombie(const sf::Texture &m_tex, const sf::Texture &m_shadow) :  m_spr(m_tex),shadow(m_shadow) {
    m_scale = sf::Vector2f(0.6,0.6); m_spr.setScale(m_scale);
    scale = sf::Vector2i(32,32);
    m_spr.setTextureRect({{0,0},{scale}}); m_spr.setOrigin({16,16}); shadow.setOrigin({9,3}); shadow.setScale({0.6,0.6});
    m_spr.setPosition({100.f, 100.f});
    hitbox.setSize({10,3}); hitbox.setPosition({m_spr.getPosition().x-6,m_spr.getPosition().y+4}); hitbox.setFillColor(sf::Color::Red);
    m_speed = 40; color = m_spr.getColor();
}

void zombie::update(float delta,mapa &mapa) {
    prevPos = m_spr.getPosition(); hitboxPrevPos = hitbox.getPosition();
    if (this->inRaduis()) {this->move(delta,mapa);}
    shadow.setPosition({m_spr.getPosition().x, m_spr.getPosition().y+10});
    this->updateHealth();
    // std::cout<<corazones<<std::endl;
}

void zombie::updateTexture() {
    sf::IntRect rect = m_spr.getTextureRect();
    if (state == 0) {
        if (ismoving) {
            if (rect.position.x >= 96) {
                rect.position.x = 0;
            }
            m_spr.setTextureRect({{rect.position.x + 32, 64},{scale}});
        }else {
            if (rect.position.x >= 160) {
                rect.position.x = 0;
            }
            m_spr.setTextureRect({{rect.position.x + 32, 0},{scale}});
        }
    }

    damageColor(damaged);
    if (!this->isAlive()) deathDraw();

}

void zombie::draw(sf::RenderWindow &m_win) {
    if (isAlive()) m_win.draw(shadow);

}

void zombie::drawHitbox(sf::RenderWindow &m_win) {
    hitbox.setFillColor(sf::Color::Red);
    m_win.draw(hitbox);
}

void zombie::syncHitbox() {
    hitbox.setPosition({m_spr.getPosition().x-6,m_spr.getPosition().y+4});
}

void zombie::colx(sf::FloatRect hitbox) {
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

void zombie::coly(sf::FloatRect hitbox) {
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

sf::Sprite &zombie::getSprite() { return m_spr;}


void zombie::move(float delta,mapa &mapa) {
    //diferencia x,y entre el player y la entidad
    dif = pl_pos - m_spr.getPosition();

    //distancia player y entidad
    dist = sqrt(dif.x * dif.x + dif.y * dif.y);
    if (dist != 0.f) { dif /= dist;}
    if (dist > 21){ismoving = true;} else{ismoving = false;}
    if (dif.x < 0){m_spr.setScale({-m_scale.x,m_scale.y});} else{m_spr.setScale(m_scale);}
    // std::cout << dist << std::endl;
    //{1,-1}
    //dif seria la "direccion"
    if (timer3.getElapsedTime().asSeconds() >= 0.1f) {
        if(iscolx){
            if(dif.x<0){
            dif={1,0};
            }else{
            dif={-1,0};
            }
        }else if(iscoly){
            if(dif.y<0){
            dif={0,1};
            }else{
            dif={0,-1};
            }
        }
        timer3.restart();
    }
    m_spr.move(dif*m_speed*delta);
    this->syncHitbox();
    for (auto &box : *hitboxes) {
        colx(box);
    }
    this->syncHitbox();
    for (auto &box : *hitboxes) {
        coly(box);
    }
    this->syncHitbox();
}

void zombie::getPlyPos(const sf::Vector2f &pl_pos) {
    this->pl_pos = pl_pos;
}

bool zombie::inRaduis() {
    dist2 = (m_spr.getPosition().x - pl_pos.x) * (m_spr.getPosition().x - pl_pos.x) + (m_spr.getPosition().y - pl_pos.y) * (m_spr.getPosition().y - pl_pos.y);

    if (dist2 < 600*600 && dist2 > 20*20) {return true;}
    return false;
}

sf::FloatRect zombie::getHitbox(){
    return m_spr.getGlobalBounds();
}

const sf::Vector2f zombie::attack(){
    return sf::Vector2f();
}

int zombie::getHealth(){
    return health;
} 

bool zombie::isAlive(){
    return vivo;
}

void zombie::updateHealth() {
    if (health < 0) health = 0;
    if (health == 0) {vivo = false; state = 1;}
    if (health > 0) {vivo = true; state = 0;}
}

void zombie::RecieveDamage() {
    std::cout << "GOLPE RECIBIDO AL ZOMBIE" << std::endl;
    damaged = true;
    if (health > 0) {
        health--;
    }
}

void zombie::deathDraw() {
    sf::IntRect rect = m_spr.getTextureRect();
    if (state == 1) {rect.position.x = 0; state = 2; count = 0;}
    if (count < 4) {m_spr.setTextureRect({{rect.position.x + 32,192},{scale}}); count++;}

}

void zombie::damageColor(bool cond) {
    if (cond) {
        m_spr.setColor(sf::Color::Red);
        damaged = false;
    }else {
        m_spr.setColor(color);
    }
}

sf::Vector2f zombie::getPosition() {
    return m_spr.getPosition();
}

