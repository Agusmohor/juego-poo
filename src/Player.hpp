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

    void update() override;
    void draw(sf::RenderWindow &m_win) override;
    void texture() override;

    void m_mouse(const sf::Vector2f &mouseCoords);
    void move() override;
    void speed();
    bool cond();

    void updateSkinByMouse(const sf::Vector2f &mouseCoords);
    sf::Vector2f getPosition() const ;


private:
    sf::Texture m_txt,text1,text2,text3;
    sf::Sprite m_spr;
    float m_speed,dx,dy,m_angle; int stamina;
    sf::Vector2f pl_pos,dir;
    sf::Keyboard::Key wKey,aKey,sKey,dKey;
    sf::Mouse::Button rClick;
};

#endif