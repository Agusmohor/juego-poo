#pragma once
#ifndef PAUSE_HPP
#define PAUSE_HPP

#include "Scene.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Game.hpp"

enum struct type {
    resume,
    setting,
    exit
};

class PauseScene : public scene{
public:
    PauseScene();
    void update(float delta,Game &m_gam)override;
    void updateView(Game &m_gam) override;
    void draw(sf::RenderWindow &win)override;
    void backMatch(Game &m_gam);
    void button_overlay(const sf::RenderWindow &win,sf::RectangleShape &button, type t);
private:
    sf::Font m_font;
    sf::Text m_text,resumeText,settingText,exitText;
    sf::RectangleShape overlay, resume,exit_button, setting;
    sf::Texture boton,botonselec;
    bool exit = false;
};

#endif