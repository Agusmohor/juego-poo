#include "menu.hpp"
#include "Match.hpp"
#include "Game.hpp"
#include <iostream>

menu::menu() : m_text1(m_font1,""), m_text2(m_font1,""), m_text3(m_font2,"") {
    this->buttons();
}

void menu::update(Game &m_gam){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) m_gam.setScene(new match);
    this->newMatch(m_gam);
    this->titleColor();
}

void menu::updateView(Game &m_gam){}

void menu::draw(sf::RenderWindow &m_win){
    this->dibujado(m_win);
    this->button_overlay(m_win);
    
}

void menu::dibujado(sf::RenderWindow &m_win){
    m_win.draw(m_text1);
    m_win.draw(m_text2);

    m_win.draw(shape);
    m_win.draw(m_text3);
}

void menu::titleColor(){
    if (timer.getElapsedTime().asSeconds() >= 0.28f) {
        // cambiar color
        r=rand();b=rand();g=rand();
        m_text1.setFillColor(sf::Color(r,g,b));
        timer.restart();
    }

}
//crea todos los botones del menu
void menu::buttons(){
    if(!m_font1.openFromFile("../assets/fonts/fuente.ttf")) throw std::runtime_error("error");
    if(!m_font2.openFromFile("../assets/fonts/MineFont.ttf")) throw std::runtime_error("error"); 
    m_text1.setFont(m_font1); m_text1.setString("Jueguito"); 
    m_text2.setFont(m_font1); m_text2.setString("press Enter to start"); 
    m_text3.setFont(m_font2); m_text3.setString("Settings");

    m_text1.setCharacterSize(100);
    m_text1.setPosition(sf::Vector2f(220,150));

    m_text2.setCharacterSize(30);
    m_text2.setFillColor(sf::Color(150,150,150));
    m_text2.setPosition(sf::Vector2f(250,450));


    m_text3.setCharacterSize(15);
    m_text3.setFillColor(sf::Color::White);
    m_text3.setPosition(sf::Vector2f(358,535));

    shape.setSize({220.f,30.f});
    shape.setPosition({sf::Vector2f(290,520)});
    if(!boton.loadFromFile("../assets/textures/Boton.png")) throw std::runtime_error("no se pudo abrir el archivo");
    if(!botonselec.loadFromFile("../assets/textures/Botonselec.png")) throw std::runtime_error("no se pudo abrir el archivo");

}

//cambia el overlay si el cursor esta encima del boton
void menu::button_overlay(const sf::RenderWindow &m_win){
    mouse_pos=sf::Mouse::getPosition(m_win);

    posx1=shape.getPosition().x; posy1=shape.getPosition().y;
    posx2=posx1+shape.getSize().x; posy2=posy1+shape.getSize().y;

    if(mouse_pos.x>=posx1 && mouse_pos.x<=posx2 && mouse_pos.y>=posy1 && mouse_pos.y<=posy2){
        shape.setTexture(&botonselec);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){  ispressed = true;  }
    }else{
        shape.setTexture(&boton);
    }
}

void menu::newMatch(Game &m_gam) {
    if (ispressed) {
        m_gam.setScene(new match);
        ispressed = false;
    }
}