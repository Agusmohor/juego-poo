#pragma once
#ifndef MENU_HPP
#define MENU_HPP
#include "Scene.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

class menu : public scene{
public:
    menu();
    void update(float delta,game &m_gam)override;
    void draw(sf::RenderWindow &win)override;

    void buttons();
    void buttonPressed(type t) override;

    //void newMatch(Game &m_gam);

    void titleColor();
    void dibujado(sf::RenderWindow &m_win);
private:
    void ProcessEvent(game &game, sf::Event &event) override;
    sf::Font m_font1,m_font2;
    sf::Text m_text1,m_text2,loadText, exitText, newText, notsavefound;
    sf::Texture boton,botonselec;
    sf::Clock timer;
    unsigned char r,g,b;
    sf::RectangleShape loadButton,newButton,exitButton;
    float posx1,posx2,posy1,posy2;
    bool ispressed = false;
    bool isNewGame = false;
    bool isLoadGame = false;
    bool isExit = false;
    bool notFound = false;
};

#endif