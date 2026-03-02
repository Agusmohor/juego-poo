#pragma once
#ifndef MENU_HPP
#define MENU_HPP
#include "core/Scene.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "settingsScene.hpp"
#include "rankingScene.hpp"
#include "ui/InputText.hpp"

class menu : public scene{
    sf::Font m_font1,m_font2;
    sf::Text m_text1,m_text2,loadText, exitText, newText, rankText, notsavefound, nameText, currname, confirm,t_settings;
    sf::Texture boton,botonselec;
    sf::Clock timer;
    unsigned char r,g,b;
    sf::RectangleShape loadButton,newButton,exitButton, rankingButton, enterName,settingsBtn;
    float posx1,posx2,posy1,posy2;
    bool ispressed = false;
    bool isNewGame = false;
    bool isLoadGame = false;
    bool isExit = false;
    bool isRanking = false;
    bool isSetting = false;
    bool notFound = false;
    bool waitingName = false;

    bool isOpened = false;

    stats m_stats;
    InputText input;
    rankingScene rankScene;
    settingsScene setScene;

    void dibujado(sf::RenderWindow &m_win);
    void buttons();
    void titleColor();
    void ProcessEvent(game &game, sf::Event &event) override;
    void buttonPressed(type t) override;
public:
    menu();
    void update(float delta,game &m_gam)override;
    void draw(sf::RenderWindow &win)override;
};

#endif