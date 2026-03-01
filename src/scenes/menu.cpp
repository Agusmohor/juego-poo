#include "scenes/menu.hpp"
#include "scenes/Match.hpp"
#include "core/Game.hpp"
#include <iostream>

menu::menu() : m_text1(m_font1), m_text2(m_font1), loadText(m_font2), newText(m_font2), exitText(m_font2), rankText(m_font1),notsavefound(m_font1), nameText(m_font1), currname(m_font1), input(m_font2), confirm(m_font2){
    buttons();
}

void menu::update(float delta,game &m_gam){
    if (m_gam.getIsOver()){rankScene.save(m_gam.getStats());rankScene.load(); rankScene.sortList();m_gam.setIsOver(false); }
    if(isNewGame) {m_gam.newProgress(); m_gam.loadProgress();m_gam.setScene(new match);}
    if(isLoadGame) {
        if (!m_gam.loadProgress()) {notFound = true;}
        else{m_gam.setScene(new match);}
    }
    if (rankScene.getBackRequest()){isRanking = false; rankScene.setBackRequest(false);}
    if (isRanking){rankScene.update(delta,m_gam);}
    if(isExit) {m_gam.exit();}
    titleColor();
    input.update();
    if (m_stats.name != "null") {
        m_gam.setStats(m_stats);
    }
    currname.setString(m_gam.getStats().name);
}

void menu::draw(sf::RenderWindow &m_win){
    if (isRanking){rankScene.draw(m_win); return;}
    dibujado(m_win);
    button_overlay(m_win,newButton,botonselec,boton);
    button_overlay(m_win,loadButton,botonselec,boton);
    button_overlay(m_win,exitButton,botonselec,boton);
    button_overlay(m_win,rankingButton,botonselec,boton);
    button_overlay(m_win,enterName,botonselec,boton);

}

void menu::dibujado(sf::RenderWindow &m_win){
    m_win.draw(m_text1);
    m_win.draw(m_text2);

    m_win.draw(newButton);
    m_win.draw(loadButton);
    m_win.draw(exitButton);
    m_win.draw(rankingButton);
    m_win.draw(enterName);
    m_win.draw(newText);
    m_win.draw(loadText);
    m_win.draw(exitText);
    m_win.draw(rankText);
    m_win.draw(nameText);
    m_win.draw(input);
    if (!(currname.getString() == "null")){m_win.draw(currname);}
    if (notFound) {m_win.draw(notsavefound);}
    if (waitingName) {m_win.draw(confirm);}
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
void menu::buttons() {
    if(!m_font1.openFromFile("../assets/fonts/fuente.ttf")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_FONT");
    if(!m_font2.openFromFile("../assets/fonts/MineFont.ttf")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_FONT");
    if(!boton.loadFromFile("../assets/textures/Boton.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");
    if(!botonselec.loadFromFile("../assets/textures/Botonselec.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");
    m_font2.setSmooth(false);

    m_text1.setFont(m_font1); m_text1.setString("Jueguito");
    m_text2.setFont(m_font1); m_text2.setString("Welcome");
    newText.setFont(m_font2); newText.setString("New game");

    m_text1.setCharacterSize(100);
    m_text1.setPosition(sf::Vector2f(220,50));

    m_text2.setCharacterSize(40);
    m_text2.setFillColor(sf::Color(150,150,150));
    m_text2.setPosition(sf::Vector2f(310,m_text1.getPosition().y+140));


    newText.setCharacterSize(20);
    newText.setFillColor(sf::Color::White);

    newButton.setSize({220.f,35.f});
    newButton.setPosition({sf::Vector2f(290,520)});

    notsavefound = newText;
    notsavefound.setFont(m_font2); notsavefound.setPosition({newText.getPosition().x-43,newText.getPosition().y-40});
    notsavefound.setString("Not save found");

    rankingButton = newButton;

    loadButton = newButton; loadButton.setPosition({newButton.getPosition().x,newButton.getPosition().y + 45});
    loadText = newText; loadText.setString("Load game");
    rankingButton = loadButton; rankingButton.setPosition({loadButton.getPosition().x,loadButton.getPosition().y + 45});
    rankText = loadText; rankText.setString("Ranking");

    exitButton = rankingButton; exitButton.setPosition({rankingButton.getPosition().x,rankingButton.getPosition().y + 45});
    exitText = newText; exitText.setString("Exit");
    centerTextToButton(loadText,loadButton);
    centerTextToButton(newText,newButton);
    centerTextToButton(exitText,exitButton);
    centerTextToButton(rankText,rankingButton);

    enterName = newButton;
    enterName.setPosition({newButton.getPosition().x,newButton.getPosition().y-100});
    nameText = newText; nameText.setString("Enter your name");
    nameText.setPosition({newText.getPosition().x-48,newText.getPosition().y-140});
    currname = newText;

    input.setPosition({nameText.getPosition().x,nameText.getPosition().y + 40});
    input.setFillColor(sf::Color::White); input.setCharacterSize(20);

    confirm = nameText; confirm.setString("Press enter to confirm...");
    confirm.setCharacterSize(18);
    confirm.setPosition({nameText.getPosition().x-30,nameText.getPosition().y + 90});

    currname.setPosition({m_text2.getPosition().x+115,m_text2.getPosition().y + 80});

}



void menu::buttonPressed( type t) {
    switch(t) {
        case type::newgame: isNewGame = true; break;
        case type::loadgame: isLoadGame = true; break;
        case type::exitgame: isExit = true; break;
        case type::ranking : isRanking = true; break;
        case type::enterName : waitingName = true; break;
    }
}

void menu::ProcessEvent(game &game, sf::Event &event) {
    if (isRanking){rankScene.ProcessEvent(game,event);return;}
    if (const auto* evt = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (evt->button==sf::Mouse::Button::Left) {
            auto &win = game.getWindow();
            if (mouseOver(win,newButton)) {buttonPressed(type::newgame);}
            if (mouseOver(win,loadButton)) {buttonPressed(type::loadgame);}
            if (mouseOver(win,exitButton)) {buttonPressed(type::exitgame);}
            if (mouseOver(win,rankingButton)) {buttonPressed(type::ranking);}
            if (mouseOver(win,enterName)) {buttonPressed(type::enterName);}else{waitingName = false;}
        }
    }
    if (const auto* evt = event.getIf<sf::Event::KeyPressed>()) {
        if (evt->scancode == sf::Keyboard::Scancode::Enter && waitingName) {
            m_stats.name = input.getValue();
            waitingName = false;
        }
    }
    if (waitingName) input.processEvent(event);
}



