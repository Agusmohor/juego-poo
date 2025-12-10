#include "menu.hpp"
#include "Match.hpp"
#include "Game.hpp"

menu::menu() : m_font1("../assets/fonts/fuente.ttf"),m_font2("../assets/fonts/MineFont.ttf"),m_text1(m_font1,"Jueguito"),m_text2(m_font1,"press Enter to start"),m_text3(m_font2,"Settings"),shape({220.f,30.f}),boton("../assets/textures/Boton.png"),botonselec("../assets/textures/Botonselec.png"){
    sf::Vector2f BotSet(290,520);
    shape.setPosition({BotSet});

    m_text1.setCharacterSize(100);
    sf::Vector2f v(220,150);
    m_text1.setPosition(v);

    m_text2.setCharacterSize(30);
    m_text2.setFillColor(sf::Color(150,150,150));
    sf::Vector2f g(250,450);
    m_text2.setPosition(g);


    m_text3.setCharacterSize(15);
    m_text3.setFillColor(sf::Color::White);
    sf::Vector2f h(358,535);
    m_text3.setPosition(h);
}

void menu::update(Game &m_gam){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) m_gam.setScene(new match);
    if (timer.getElapsedTime().asSeconds() >= 0.28f) {
        // cambiar color
        r=rand();b=rand();g=rand();
        m_text1.setFillColor(sf::Color(r,g,b));
        timer.restart();
    }
   
}

void menu::draw(sf::RenderWindow &m_win){
    m_win.clear(sf::Color::Black);
    m_win.draw(m_text1);
    m_win.draw(m_text2);

    mouse_pos=sf::Mouse::getPosition(m_win);
    posx1=shape.getPosition().x;
    posy1=shape.getPosition().y;
    posx2=posx1+shape.getSize().x;
    posy2=posy1+shape.getSize().y;
    if(mouse_pos.x>=posx1 && mouse_pos.x<=posx2 && mouse_pos.y>=posy1 && mouse_pos.y<=posy2){
        shape.setTexture(&botonselec);
    }else{
        shape.setTexture(&boton);
    }
    m_win.draw(shape);
    m_win.draw(m_text3);
}