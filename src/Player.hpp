#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/View.hpp>
#include "Hud.hpp"
#include "Entity.hpp"

class player : public entity{
public:
    player();
    void update() override;
    void draw(sf::RenderWindow &m_win) override;
    void texture() override;
    void m_mouse(sf::RenderWindow &m_win);
    void m_key();
    void viewCentre(sf::RenderWindow &m_win);
    void speed();
    bool cond();
private:
    sf::View m_view;
    sf::Texture m_txt,text1,text2,text3;
    sf::Sprite m_spr;
    float m_speed,dx,dy,m_angle; int stamina;
    sf::Vector2f pl_pos,dir, mouseCoords;
    sf::Vector2i posMouse;
    sf::Keyboard::Key wKey,aKey,sKey,dKey;
    sf::Mouse::Button rClick;
    hud m_hud;

};

#endif