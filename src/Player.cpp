#include "Player.hpp"
#include <cmath>
#include "Mapa.hpp"
#include <iostream>
#include "Tree.hpp"

player::player(const sf::Texture &sprite,const sf::Texture &shadow) :  m_spr(sprite),m_shadow(shadow),m_speed(5),stamina(180){
    scale = sf::Vector2i(32,32);
    m_spr.setTextureRect({{0,0},{scale}});
    m_scale = sf::Vector2f(0.6,0.6); m_spr.setScale(m_scale); m_shadow.setScale(m_scale); m_shadow.setOrigin({9,3});
    m_spr.setOrigin({16,16}); m_spr.setPosition({80,80});
    dir.x = 0.f; dir.y = 0.f;
    wKey = sf::Keyboard::Key::W;aKey = sf::Keyboard::Key::A;sKey = sf::Keyboard::Key::S;dKey = sf::Keyboard::Key::D;
    rClick = sf::Mouse::Button::Right;
    lClick = sf::Mouse::Button::Left;
    hitbox.setSize({10,3}); hitbox.setPosition({m_spr.getPosition().x-6,m_spr.getPosition().y+4}); hitbox.setFillColor(sf::Color::Blue);
}

void player::move(float delta, mapa &mapa) {
    dir.x = 0.f; dir.y = 0.f;
    //interaccion teclas
    if (!colision) {
        if(sf::Keyboard::isKeyPressed(wKey) && !sf::Keyboard::isKeyPressed(sKey)) {
            dir.y = -1.f;
        }
        if(sf::Keyboard::isKeyPressed(sKey) && !sf::Keyboard::isKeyPressed(wKey)) {
            dir.y = 1.f;
        }
        if(sf::Keyboard::isKeyPressed(dKey) && !sf::Keyboard::isKeyPressed(aKey)) {
            dir.x = 1.f; m_spr.setScale(m_scale);
        }
        if(sf::Keyboard::isKeyPressed(aKey) && !sf::Keyboard::isKeyPressed(dKey)) {
            dir.x = -1.f; m_spr.setScale({-m_scale.x,m_scale.y});
        }
    }

    //normalizar direccion
    if (dir.x != 0 && dir.y != 0) {
        float length = sqrt(dir.x*dir.x + dir.y*dir.y);
        dir /= length;
    }
    //speed
    speed();
    sf::Vector2f velocity = dir * m_speed *delta;
    prevPos = m_spr.getPosition(); syncHitbox();
    sf::FloatRect hb = hitbox.getGlobalBounds();

    float dx = velocity.x;
    if (dx != 0.f){
        float probeX = (dx > 0.f) ? (hb.position.x + hb.size.x + dx + 10.f) : (hb.position.x + dx - 10.f);
        bool top    = mapa.isSolidAtPixel(probeX, hb.position.y + 10.f);
        bool midx    = mapa.isSolidAtPixel(probeX,hb.position.y + hb.size.y * 0.5f);
        bool bottom = mapa.isSolidAtPixel(probeX, hb.position.y + hb.size.y - 8.f);
        if (!top && !bottom && !midx) m_spr.move({dx, 0.f});
    }

    syncHitbox();
    for (auto& box : *hitboxes) colx(box);

    hb = hitbox.getGlobalBounds();
    float dy = velocity.y;
    if (dy != 0.f){
        float probeY = (dy > 0.f) ? (hb.position.y + hb.size.y + dy + 24.f) : (hb.position.y + dy - 5.f);
        bool left  = mapa.isSolidAtPixel(hb.position.x + 10.f, probeY);
        bool midy = mapa.isSolidAtPixel(hb.position.x + hb.size.x * 0.8f, probeY);
        bool right = mapa.isSolidAtPixel(hb.position.x + hb.size.x - 10.f, probeY);
        if (!left && !right && !midy) m_spr.move({0.f, dy});
    }

    syncHitbox();
    for (auto& box : *hitboxes) coly(box);

}



void player::texture(){
    if (!sf::Mouse::isButtonPressed(rClick) && (sf::Keyboard::isKeyPressed(wKey) || sf::Keyboard::isKeyPressed(aKey) || sf::Keyboard::isKeyPressed(sKey) || sf::Keyboard::isKeyPressed(dKey) )) {
         state = 1;
    }else {
         state = 0;
    }


}

void player::updateTexture() {
    sf::IntRect rect = m_spr.getTextureRect();
    if (isAttacking) state = 5;
    if (iscritic) state = 6;
    switch (state) {
        case 0:
            if (rect.position.x >= 192) {
                rect.position.x = 0;
            }
            m_spr.setTextureRect({{rect.position.x + 32, 0},{scale}});
            break;
        case 1:
            if (rect.position.x >= 96) {
                rect.position.x = 0;
            }
            m_spr.setTextureRect({{rect.position.x + 32, 65},{scale}});
            break;
        case 2:
            if (rect.position.x >= 224) {
                rect.position.x = 0;
            }
            m_spr.setTextureRect({{rect.position.x + 32,97},{scale}});
            break;
        case 5:
            if (rect.position.x >= 160) {
                isAttacking = false;
                rect.position.x = 0;
            }
            if (isAttacking) {
                m_spr.setTextureRect({{rect.position.x + 32,289},{scale}});
            }
            break;
        case 6:
            if (rect.position.x >= 224) {
                iscritic = false;
                rect.position.x = 0;
            }
            if (iscritic) {
                m_spr.setTextureRect({{rect.position.x + 32, 256},{scale}});
            }
            break;

    }
    if (!isAlive()) deathDraw();

}

void player::speed(){
    m_speed = 50;
    if (staminaCooldown.getElapsedTime().asMilliseconds() >= 50) {
        if(stamina < 180){
            stamina++;
        }
        staminaCooldown.restart();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && stamina > 0 && this->cond() && !empty_stamina){
        stamina--; m_speed *= 1.2; state = 2;
    }

    if (stamina == 0) empty_stamina = true;
    if (stamina == 180) empty_stamina = false;
    // std::cout << "stam " << stamina << " vel " << m_speed<<std::endl;
}

bool player::cond(){
    if(sf::Keyboard::isKeyPressed(wKey)) return true;
    if(sf::Keyboard::isKeyPressed(aKey)) return true;
    if(sf::Keyboard::isKeyPressed(sKey)) return true;
    if(sf::Keyboard::isKeyPressed(dKey)) return true;

    return false;
}

//movimiento enfoque mouse
void player::m_mouse(const sf::Vector2f &mouseCoords){
    //interaccion mouse
    //dx  //dx y dy, son las distancias entre el personaje, y el cursor en ese momento, (coords cursor - coords player)
    dx = mouseCoords.x - pl_pos.x; dy = mouseCoords.y - pl_pos.y;
    //angulo entre el player y el cursor (0-180)
    m_angle = atan2(dy,dx); m_angle *= 180 / 3.14;
    // if(m_angle < 0 && m_angle > -90) m_spr.setTexture(sprite);
    // if(m_angle <= -90 && m_angle >= -180) m_spr.setTexture(sprite);
    // if(m_angle > 90 && m_angle < 180) m_spr.setTexture(sprite);
    // if(m_angle <= 90 && m_angle >= 0) m_spr.setTexture(sprite);
        
    // std::cout << "ang " << m_angle << " dx " << dx<< " dy " << dy << " posmouse " << mouseCoords.x << " x "<< mouseCoords.y << " y "<<std::endl;
    // std::cout << mouseCoords.x << " " << mouseCoords.y <<std::endl;aW
}


void player::update(float delta,mapa &mapa) {
    prevPos = m_spr.getPosition(); hitboxPrevPos = hitbox.getPosition();
    //actualizar player
    texture();
    if (!isAttacking && !iscritic) { move(delta,mapa);}

    // std::cout << health << std::endl;
    if (health >= 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) health--;
    }
    if (health <= 0) health = 0;
    //el jugador se muere si su vida es 0, el state = 4, es para controlar el updateTexture
    if (health == 0 && state != 4){ vivo = false; state = 3;} else {vivo = true;}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) health++;
    if (health >= 14) health = 14;
    // std::cout << this->getPosition().x << " " << this->getPosition().y << std::endl;

    m_shadow.setPosition({m_spr.getPosition().x, m_spr.getPosition().y+10});
    //sf::Vector2f delta1 = dir * m_speed;
    //pl_pos=m_spr.getPosition();
    //m_spr.move(delta1);
    if (cooldown.getElapsedTime().asSeconds() >= 0.1f) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ) { attackSkin(); getScale();}
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) { criticSkin();}
        cooldown.restart();
    }

}

void player::draw(sf::RenderWindow& m_win) {
    if (state != 4) m_win.draw(m_shadow);

}

void player::updateSkinByMouse(const sf::Vector2f &mouseCoords){
    m_mouse(mouseCoords);
}

//posicion del player
sf::Vector2f player::getPosition() const {
    return m_spr.getPosition();
}

sf::FloatRect player::getHitbox(){
    return m_spr.getGlobalBounds();
}

void player::attackSkin(){
    if (!isAttacking) {
        state = 5; isAttacking = true; isHitting = true;
        m_spr.setTextureRect({{0,289},{scale}});
    }
}

void player::criticSkin(){
    if (!iscritic) {
        state = 6; iscritic = true;
        m_spr.setTextureRect({{0,256},{scale}});
    }
}

int player::getHealth(){
    return health;
}

int player::getStamina() {
    return stamina;
}

bool player::isAlive(){
    return vivo;
}

bool player::isStaminaEmpty() {
    return empty_stamina;
}

void player::recieveDamage() {
    damaged = true;
    health--;
}

sf::Sprite &player::getSprite(){ return m_spr; }


void player::colx(sf::FloatRect hitbox) {
    if (this->hitbox.getGlobalBounds().findIntersection(hitbox).has_value()) {
        m_spr.setPosition({prevPos.x,m_spr.getPosition().y});
        this->hitbox.setPosition({hitboxPrevPos.x,this->hitbox.getPosition().y});
    }

}

void player::coly(sf::FloatRect hitbox) {
    if (this->hitbox.getGlobalBounds().findIntersection(hitbox).has_value()) {
        m_spr.setPosition({m_spr.getPosition().x,prevPos.y});
        this->hitbox.setPosition({this->hitbox.getPosition().x,hitboxPrevPos.y});
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
    if (health <= 0) {health = 0;vivo = false;}
    else {vivo = true;}

}

void player::deathDraw() {
    sf::IntRect rect = m_spr.getTextureRect();
    if (state == 3) rect.position.x = 0; state = 4;
    m_spr.setTextureRect({{rect.position.x + 32,192},{scale}});

}

const sf::Vector2f player::getScale() {
    return m_spr.getScale();
}

const bool player::getHitStatus() const {return isHitting;}
void player::setHitStatus(bool status) {isHitting = status;}

