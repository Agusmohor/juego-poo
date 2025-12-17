#include "Hud.hpp"

hud::hud() : hobTexture("../assets/textures/entity/player/gui/entire_hotbar.png"), hselTe("../assets/textures/entity/player/gui/selected.png"), hotbarBar(hobTexture),hsel(hselTe) {
    if(!hselTe.loadFromFile("../assets/textures/entity/player/gui/selected.png")) throw std::runtime_error("error al cargar hud");
    k_1 = sf::Keyboard::Key::Num1;k_2 = sf::Keyboard::Key::Num2;k_3 = sf::Keyboard::Key::Num3;
    k_4 = sf::Keyboard::Key::Num4;k_5 = sf::Keyboard::Key::Num5;k_6 = sf::Keyboard::Key::Num6;
    hotbarBar.setOrigin(sf::Vector2f(48,16));
    hotbarBar.setScale(sf::Vector2f(4,4));
    hsel.setOrigin(sf::Vector2f(8,16)); hsel.setScale(sf::Vector2f(4,4));
    hsel.setPosition(sf::Vector2f(240,798));
    // hotbarBar.setTextureRect(sf::IntRect({0,0},{16,16}));
    hotbarBar.setPosition(sf::Vector2f(400,798));
}



void hud::draw(sf::RenderWindow &m_win){
    m_win.draw(hotbarBar);
    m_win.draw(hsel);
}

void hud::update(){
    hud::keyBoard();
}

void hud::keyBoard(){
    if(sf::Keyboard::isKeyPressed(k_1))hsel.setPosition(sf::Vector2f(240,798));
    if(sf::Keyboard::isKeyPressed(k_2))hsel.setPosition(sf::Vector2f(304,798));
    if(sf::Keyboard::isKeyPressed(k_3))hsel.setPosition(sf::Vector2f(368,798));
    if(sf::Keyboard::isKeyPressed(k_4))hsel.setPosition(sf::Vector2f(432,798));
    if(sf::Keyboard::isKeyPressed(k_5))hsel.setPosition(sf::Vector2f(496,798));
    if(sf::Keyboard::isKeyPressed(k_6))hsel.setPosition(sf::Vector2f(560,798));
}