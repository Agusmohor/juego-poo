#include "Hud.hpp"
#include <iostream>

hud::hud() : hobTexture("../assets/textures/entity/player/gui/entire_hotbar.png"), hselTe("../assets/textures/entity/player/gui/selected.png"), hotbarBar(hobTexture),hsel(hselTe) {
    if(!hselTe.loadFromFile("../assets/textures/entity/player/gui/selected.png")) throw std::runtime_error("error al cargar hud");
    k_1 = sf::Keyboard::Key::Num1;k_2 = sf::Keyboard::Key::Num2;k_3 = sf::Keyboard::Key::Num3;
    k_4 = sf::Keyboard::Key::Num4;k_5 = sf::Keyboard::Key::Num5;k_6 = sf::Keyboard::Key::Num6;
    hotbarBar.setOrigin(sf::Vector2f(48,16));
    hotbarBar.setScale(sf::Vector2f(4,4));
    hsel.setOrigin(sf::Vector2f(8,16)); hsel.setScale(sf::Vector2f(4,4));
    hselpos = sf::Vector2f(240,798);
    hsel.setPosition(hselpos);
    hotbarBar.setPosition(sf::Vector2f(400,798));
}



void hud::draw(sf::RenderWindow &m_win){
    m_win.draw(hotbarBar);
    m_win.draw(hsel);
}

void hud::update(){
    this->keyBoard();
}

void hud::updateView(){
    //reposicionamiento del hud con el resize
    hotbarBar.setPosition(sf::Vector2f(400,newpos));
    hselpos = sf::Vector2f(hselpos.x,newpos);
    hsel.setPosition(hselpos);
}

void hud::keyBoard(){
    if(sf::Keyboard::isKeyPressed(k_1)) hselpos = sf::Vector2f(240,newpos);
    if(sf::Keyboard::isKeyPressed(k_2)) hselpos = sf::Vector2f(304,newpos);
    if(sf::Keyboard::isKeyPressed(k_3)) hselpos = sf::Vector2f(368,newpos);
    if(sf::Keyboard::isKeyPressed(k_4)) hselpos = sf::Vector2f(432,newpos);
    if(sf::Keyboard::isKeyPressed(k_5)) hselpos = sf::Vector2f(496,newpos);
    if(sf::Keyboard::isKeyPressed(k_6)) hselpos = sf::Vector2f(560,newpos);
}


void hud::moveHotbar(const sf::Vector2f &winview){
        m_winSize = winview;
        newpos = m_winSize.y-2;
}

