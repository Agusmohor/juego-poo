#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>
#include "Stats.hpp"
#include <SFML/Window/Event.hpp>

class game;

enum struct type {
    resume,
    setting,
    newgame,
    loadgame,
    exitgame,
    mainmenu,
    ranking,
    back,
    save,
    Ab1, Ab2, Ab3, Ab4
};

class scene {
public:
    virtual ~scene() = default;
    virtual void ProcessEvent(game &game, sf::Event &event) {};
    virtual void update(float delta,game &m_gam) = 0;
    virtual void updateView(game &m_gam) {};
    virtual void draw(sf::RenderWindow &m_win) = 0;
    virtual void button_overlay(const sf::RenderWindow &win, sf::RectangleShape &button, type t, sf::Texture &botonSel, sf::Texture &buton);
    virtual void buttonPressed(type t) {};
    virtual bool clickOn(const sf::RenderWindow &win, const sf::RectangleShape &btn);

};

#endif