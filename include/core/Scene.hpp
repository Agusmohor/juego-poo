#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>
#include "gameplay/Stats.hpp"
#include <SFML/Window/Event.hpp>
#include <cmath>

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
    enterName,
    Ab1, Ab2, Ab3, Ab4
};

class scene {
public:
    virtual ~scene() = default;
    virtual void ProcessEvent(game &game, sf::Event &event) {};
    virtual void update(float delta,game &m_gam) = 0;
    virtual void updateView(game &m_gam) {};
    virtual void draw(sf::RenderWindow &m_win) = 0;
    virtual void centerTextToButton(sf::Text &t,const sf::RectangleShape &button) {
        //recibe un texto y lo centra en el boton, primero cambia el origin del texto
        auto bbounds = button.getGlobalBounds();
        t.setOrigin({t.getLocalBounds().getCenter().x,t.getOrigin().y});
        t.setPosition(bbounds.getCenter());
    }
    virtual void buttonPressed(type t) {};
    virtual void button_overlay(const sf::RenderWindow &win, sf::RectangleShape &button, type t, sf::Texture &botonSel, sf::Texture &buton) {
        //recive un boton junto a 2 texturas, cambia de textura el boton cuando el mouse esta encima
        sf::Vector2i mouse_pos(sf::Mouse::getPosition(win).x,sf::Mouse::getPosition(win).y);
        sf::Vector2f window_pos = win.mapPixelToCoords(mouse_pos);

        if (button.getGlobalBounds().contains(window_pos)) {
            button.setTexture(&botonSel);
        }else{
            button.setTexture(&buton);
        }
    };
    virtual bool clickOn(const sf::RenderWindow &win, const sf::RectangleShape &btn) {
        //devuelve true si el mouse esta encima del shape
        auto mp = sf::Mouse::getPosition(win);
        auto wp = win.mapPixelToCoords(mp);
        return btn.getGlobalBounds().contains(wp);
    };

};

#endif