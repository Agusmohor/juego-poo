#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/View.hpp>
#include "Entity.hpp"

class player : public entity{
public:
    player();
    void update() override;
    void draw(sf::RenderWindow &m_win) override;
    void m_mouse(sf::RenderWindow &m_win);
    void m_key();
    void viewCentre(sf::RenderWindow &m_win);
    void speed();
    bool cond();
private:
    sf::View m_view;
    sf::Vector2f pl_pos;
    sf::Texture m_txt;
    sf::Sprite m_spr;
    float m_speed;
    int stamina;
    sf::Texture text1;
    sf::Texture text2;
    sf::Texture text3;
    sf::Vector2f dir;
    sf::Vector2i posMouse;
    sf::Vector2f mouseCoords;
    float dx,dy;
    float hip;
    float m_angle;

};

#endif