#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Entity.hpp"
#include "Mapa.hpp"

class player : public entity{
public:
    player();

    void update(float delta,mapa &mapa);
    void draw(sf::RenderWindow &m_win) override;
    void texture() override;
    sf::FloatRect getTheBounds() override;
    bool isAlive() override;
    int manyLife() override;
    bool attact(sf::RenderWindow &m_win,sf::FloatRect entpos) override;
    void RecieveDamage() override;

    void m_mouse(const sf::Vector2f &mouseCoords);
    void move(float delta,mapa &mapa) override;
    void speed();
    bool cond();

    void updateSkinByMouse(const sf::Vector2f &mouseCoords);
    sf::Vector2f getPosition() const ;


private:
    int corazones = 5;
    bool vivo = true;
    bool rDamage = false;
    sf::Texture m_txt,text1,text2,text3;
    sf::Sprite m_spr;
    float m_speed,dx,dy,m_angle; int stamina;
    sf::Vector2f pl_pos,dir,mouse_pos;
    sf::Keyboard::Key wKey,aKey,sKey,dKey;
    sf::Mouse::Button rClick,lClick;

    float m_width = 30.0f;  // ancho player
    float m_height = 40.0f; //altura player
};

#endif