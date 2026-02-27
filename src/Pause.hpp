#pragma once
#ifndef PAUSE_HPP
#define PAUSE_HPP

#include "Scene.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Game.hpp"
#include "settingsScene.hpp"
#include "menu.hpp"

class PauseScene : public scene{
public:
    PauseScene();
    void update(float delta,game &m_gam)override;
    void updateView(game &m_gam) override;
    void draw(sf::RenderWindow &win)override;
    void button_overlay(const sf::RenderWindow &win,sf::RectangleShape &button, type t) override;

    void buttonPressed( type t) override;
    bool clickOn(const sf::RenderWindow &win, const sf::RectangleShape &btn) override;

    void drawPause(sf::RenderWindow &m_win);

    void backMatch(game &m_gam);
private:
void ProcessEvent(game &game, sf::Event &event) override;
    sf::Font m_font;
    sf::Text m_text,resumeText,settingText,exitText;
    sf::RectangleShape overlay, resume,exit_button, setting;
    sf::Texture boton,botonselec;
    bool isResume = false;
    bool isSettings = false;
    bool isExit = false;

    settingsScene settingScene;
};

#endif