#include "scenes/GameOver.hpp"
#include "core/Game.hpp"

#include <iomanip>

#include <iostream>


gameover::gameover() : font("../assets/fonts/MineFont.ttf"), text(font), text2(font) ,mainmenuText(font), exitText(font) {
    if (!font.openFromFile("../assets/fonts/MineFont.ttf")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_FONT_FROM_FILE");
    if(!boton.loadFromFile("../assets/textures/Boton.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");
    if(!botonselec.loadFromFile("../assets/textures/Botonselec.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");
    shape.setFillColor(sf::Color::Red);
    text.setString("GAME OVER");
    text.setCharacterSize(100);
    text.setPosition({130,150});
    returnToMainMenu.setSize({220.f,35.f});
    returnToMainMenu.setPosition({sf::Vector2f(290,610)});
    exit = returnToMainMenu; exit.setPosition({returnToMainMenu.getPosition().x,returnToMainMenu.getPosition().y + 45});
    mainmenuText.setFont(font); mainmenuText.setString("Main menu");
    mainmenuText.setCharacterSize(20);
    mainmenuText.setFillColor(sf::Color::White);
    exitText = mainmenuText; exitText.setString("Quit game");
    centerTextToButton(mainmenuText,returnToMainMenu);
    centerTextToButton(exitText,exit);
}

void gameover::update(float delta, game &m_gam) {
    if (!isgameover) { m_stats = m_gam.getStats(); m_gam.setIsOver(true);isgameover = true; toText();}
    if (mainmenu) m_gam.setScene(new menu);
    if (exitgame) m_gam.exit();
}

void gameover::draw(sf::RenderWindow &m_win) {
    button_overlay(m_win,returnToMainMenu,type::mainmenu,botonselec,boton);
    button_overlay(m_win,exit,type::exitgame,botonselec,boton);
    m_win.draw(shape);
    m_win.draw(text);
    m_win.draw(text2);
    m_win.draw(returnToMainMenu);
    m_win.draw(exit);
    m_win.draw(mainmenuText);
    m_win.draw(exitText);
}

void gameover::toText() {
    int totalseg = m_stats.timeAlive;
    int min = totalseg / 60;
    int seg = totalseg % 60;
    std::ostringstream s;
    s << "Kills " << std::to_string(m_stats.kills) << " " << "tiempo vivo " << std::setw(2) << std::setfill('0') << min << ":" << std::setw(2) << std::setfill('0') << seg;
    text2.setString(s.str());
    text2.setPosition({200,300});
}

void gameover::ProcessEvent(game &game, sf::Event &event) {
    if (const auto* evt = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (evt->button == sf::Mouse::Button::Left) {
            auto &win = game.getWindow();
            if (clickOn(win,returnToMainMenu)){buttonPressed(type::mainmenu);}
            if (clickOn(win,exit)){buttonPressed(type::exitgame);}
        }
    }
}

void gameover::buttonPressed(type t) {
    switch(t) {
        case type::mainmenu: mainmenu = true; break;
        case type::exitgame: exitgame = true; break;
    }
}
