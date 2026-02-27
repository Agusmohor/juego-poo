#include "menu.hpp"
#include "Match.hpp"
#include "Game.hpp"
#include <iostream>

menu::menu() : m_text1(m_font1), m_text2(m_font1), loadText(m_font2), newText(m_font2), exitText(m_font2), rankText(m_font1),notsavefound(m_font1) {
    buttons();
}

void menu::update(float delta,game &m_gam){
    if (m_gam.getIsOver()){rankScene.save(m_gam.getStats());rankScene.load(); m_gam.setIsOver(false);}
    if(isNewGame) {m_gam.newProgress(); m_gam.loadProgress();m_gam.setScene(new match);}
    if(isLoadGame) {
        if (!m_gam.loadProgress()) {notFound = true;}
        else{m_gam.setScene(new match);}
    }
    if(isExit) {m_gam.exit();}
    titleColor();
}

void menu::draw(sf::RenderWindow &m_win){
    dibujado(m_win);
    button_overlay(m_win,newButton,type::newgame,botonselec,boton);
    button_overlay(m_win,loadButton,type::loadgame,botonselec,boton);
    button_overlay(m_win,exitButton,type::exitgame,botonselec,boton);
    button_overlay(m_win,rankingButton,type::ranking,botonselec,boton);

}

void menu::dibujado(sf::RenderWindow &m_win){
    m_win.draw(m_text1);
    m_win.draw(m_text2);

    m_win.draw(newButton);
    m_win.draw(loadButton);
    m_win.draw(exitButton);
    m_win.draw(rankingButton);
    m_win.draw(newText);
    m_win.draw(loadText);
    m_win.draw(exitText);
    m_win.draw(rankText);
    if (notFound) {m_win.draw(notsavefound);}
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
    if(!m_font1.openFromFile("../assets/fonts/fuente.ttf")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_FONT");
    if(!m_font2.openFromFile("../assets/fonts/MineFont.ttf")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_FONT");
    if(!boton.loadFromFile("../assets/textures/Boton.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");
    if(!botonselec.loadFromFile("../assets/textures/Botonselec.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");

    m_text1.setFont(m_font1); m_text1.setString("Jueguito"); 
    m_text2.setFont(m_font1); m_text2.setString("Welcome");
    newText.setFont(m_font2); newText.setString("New game");

    m_text1.setCharacterSize(100);
    m_text1.setPosition(sf::Vector2f(220,150));

    m_text2.setCharacterSize(40);
    m_text2.setFillColor(sf::Color(150,150,150));
    m_text2.setPosition(sf::Vector2f(310,290));


    newText.setCharacterSize(20);
    newText.setFillColor(sf::Color::White);
    newText.setPosition(sf::Vector2f(345,540));

    newButton.setSize({220.f,35.f});
    newButton.setPosition({sf::Vector2f(290,520)});

    notsavefound = newText;
    notsavefound.setFont(m_font2); notsavefound.setPosition({newText.getPosition().x-43,newText.getPosition().y-40});
    notsavefound.setString("Not save found");

    rankingButton = newButton;

    loadButton = newButton; loadButton.setPosition({newButton.getPosition().x,newButton.getPosition().y + 45});
    loadText = newText; loadText.setString("Load game"); loadText.setPosition({newText.getPosition().x - 8,newText.getPosition().y + 45});
    rankingButton = loadButton; rankingButton.setPosition({loadButton.getPosition().x,loadButton.getPosition().y + 45});
    rankText = loadText; rankText.setString("Ranking"); rankText.setPosition({loadText.getPosition().x+15 ,loadText.getPosition().y + 45});

    exitButton = rankingButton; exitButton.setPosition({rankingButton.getPosition().x,rankingButton.getPosition().y + 45});
    exitText = newText; exitText.setString("Exit"); exitText.setPosition({rankText.getPosition().x +20,rankText.getPosition().y + 45});
}



void menu::buttonPressed( type t) {
    switch(t) {
        case type::newgame: isNewGame = true; break;
        case type::loadgame: isLoadGame = true; break;
        case type::exitgame: isExit = true; break;
        case type::ranking : isRanking = true; break;
    }
}

void menu::ProcessEvent(game &game, sf::Event &event) {
    if (const auto* evt = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (evt->button==sf::Mouse::Button::Left) {
            auto &win = game.getWindow();
            if (clickOn(win,newButton)) {buttonPressed(type::newgame);}
            if (clickOn(win,loadButton)) {buttonPressed(type::loadgame);}
            if (clickOn(win,exitButton)) {buttonPressed(type::exitgame);}
            if (clickOn(win,rankingButton)) {buttonPressed(type::ranking);}
        }
    }
}



