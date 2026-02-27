#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class Game;

struct stats {
    float timeAlive = 0.f;
    int kills = 0;
};

enum struct type {
    resume,
    setting,
    newgame,
    loadgame,
    exit,
    save,
    Ab1, Ab2, Ab3, Ab4
};

class scene {
public:
    virtual ~scene() = default;
    virtual void ProcessEvent(Game &game, sf::Event &event) {};
    virtual void update(float delta,Game &m_gam) = 0;
    virtual void updateView(Game &m_gam) {};
    virtual void draw(sf::RenderWindow &m_win) = 0;
    virtual void button_overlay(const sf::RenderWindow &win, sf::RectangleShape &button, type t) {};

};

#endif