#include "scenes/settingsScene.hpp"
#include "core/Game.hpp"
#include <iostream>


settingsScene::settingsScene() : ab1Text(font), ab2Text(font), ab3Text(font), ab4Text(font), exitText(font), saveText(font),k1(font),k2(font),k3(font),k4(font), waitkey(font) {
    if (!font.openFromFile("../assets/fonts/MineFont.ttf")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_FONT_FROM_FILE");
    if(!boton.loadFromFile("../assets/textures/Boton.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");
    if(!botonselec.loadFromFile("../assets/textures/Botonselec.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");
    font.setSmooth(false);
    background.setSize({6000.f,6000.f});
    background.setFillColor(sf::Color(0,0,0,210));
    background.setPosition(sf::Vector2f(-2000,-2000));

    ab1Text.setFont(font); ab1Text.setCharacterSize(20); ab1Text.setString("First ability");
    ab1Text.setPosition({100.f,225.f});

    Ab1.setSize({50.f,50.f});
    Ab1.setPosition({250.f,200.f});

    Ab2 = Ab1; Ab2.setPosition({Ab1.getPosition().x,Ab1.getPosition().y + 100});
    ab2Text = ab1Text; ab2Text.setPosition({ab1Text.getPosition().x - 35,ab1Text.getPosition().y + 100}); ab2Text.setString("Second ability");

    Ab3 = Ab1; Ab3.setPosition({Ab1.getPosition().x + 300,Ab1.getPosition().y});
    ab3Text = ab1Text; ab3Text.setPosition({ab1Text.getPosition().x + 300,ab1Text.getPosition().y}); ab3Text.setString("Thrid ability");

    Ab4 = Ab3; Ab4.setPosition({Ab3.getPosition().x,Ab3.getPosition().y + 100});
    ab4Text = ab3Text; ab4Text.setPosition({ab3Text.getPosition().x - 20 ,ab3Text.getPosition().y + 100}); ab4Text.setString("Fourth ability");
    save.setSize({220.f,35.f});
    save.setPosition({sf::Vector2f(290,610)});
    exit = save; exit.setPosition({save.getPosition().x,save.getPosition().y+45});

    saveText.setFont(font); saveText.setString("Save config");
    saveText.setCharacterSize(20);
    saveText.setFillColor(sf::Color::White);
    exitText = saveText;
    exitText.setString("Exit");

    centerTextToButton(saveText,save);
    centerTextToButton(exitText,exit);

    waitkey = saveText; waitkey.setString("Press a key... (Esc to cancel)");
    waitkey.setPosition({saveText.getPosition().x-110,saveText.getPosition().y-100});

    k1 = ab1Text; k1.setPosition({265,225}); k1.setString("null");
    k2 = k1; k3 = k1, k4 = k1;
    k2.setPosition({k1.getPosition().x,k1.getPosition().y + 100});
    k3.setPosition({k1.getPosition().x + 300,k1.getPosition().y});
    k4.setPosition({k3.getPosition().x,k3.getPosition().y + 100});
    m_keys.fill(sf::Keyboard::Scancode::Unknown);
}

void settingsScene::update(float delta,game &m_game) {
    if (isRecentlyOpen) {m_keys = m_game.getKeyBinds(); isRecentlyOpen = false;}
    k1.setString(keyToString(m_keys[0]));
    k2.setString(keyToString(m_keys[1]));
    k3.setString(keyToString(m_keys[2]));
    k4.setString(keyToString(m_keys[3]));
    if (isexit) {m_game.setKeyBinds(m_keys,isSave); isSave = false;}
}

void settingsScene::draw(sf::RenderWindow &m_win) {
    button_overlay(m_win,Ab1,type::Ab1,botonselec,boton);
    button_overlay(m_win,Ab2,type::Ab2,botonselec,boton);
    button_overlay(m_win,Ab3,type::Ab3,botonselec,boton);
    button_overlay(m_win,Ab4,type::Ab4,botonselec,boton);
    button_overlay(m_win,exit,type::exitgame,botonselec,boton);
    button_overlay(m_win,save,type::save,botonselec,boton);
    m_win.draw(background);
    m_win.draw(Ab1);
    m_win.draw(Ab2);
    m_win.draw(Ab3);
    m_win.draw(Ab4);
    m_win.draw(exit);
    m_win.draw(save);
    m_win.draw(ab1Text);
    m_win.draw(ab2Text);
    m_win.draw(ab3Text);
    m_win.draw(ab4Text);
    m_win.draw(exitText);
    m_win.draw(saveText);
    m_win.draw(k1);
    m_win.draw(k2);
    m_win.draw(k3);
    m_win.draw(k4);
    if (waitingForKey){ m_win.draw(waitkey);}

}

void settingsScene::setKey(sf::Keyboard::Scancode key) {
    m_keys[static_cast<int>(curraction)] = key;
}

void settingsScene::ProcessEvent(game &game, sf::Event &event) {
    auto &win = game.getWindow();
    if (const auto* evt = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (evt->button == sf::Mouse::Button::Left) {
            if (clickOn(win,Ab1)){buttonPressed(type::Ab1);}
            if (clickOn(win,Ab2)){buttonPressed(type::Ab2);}
            if (clickOn(win,Ab3)){buttonPressed(type::Ab3);}
            if (clickOn(win,Ab4)){buttonPressed(type::Ab4);}
            if (clickOn(win,save)){buttonPressed(type::save);}
            if (clickOn(win,exit)){buttonPressed(type::exitgame);}
        }
    }
    if (const auto* evt = event.getIf<sf::Event::KeyPressed>()) {
        if (waitingForKey) {
            if (evt->code == sf::Keyboard::Key::Escape) {waitingForKey = false; return;;}
            setKey(evt->scancode);
            waitingForKey = false;
            std::cout << keyToString(evt->scancode) << std::endl;
        }
    }
}

void settingsScene::buttonPressed( type t) {
    switch(t) {
        case type::Ab1 : curraction = action::shield; waitingForKey = true; break;
        case type::Ab2 : curraction = action::dash;waitingForKey = true; break;
        case type::Ab3 : curraction = action::fire;waitingForKey = true; break;
        case type::Ab4 : curraction = action::heal;waitingForKey = true; break;
        case type::save : isSave = true; break;
        case type::exitgame : isexit = true; break;
    }
}

bool settingsScene::isWaitingForKey() const {return waitingForKey;}

bool settingsScene::getExit() const { return isexit; }
void settingsScene::setExit(bool exit) {isexit = exit;}

std::string settingsScene::keyToString(sf::Keyboard::Scancode key) {
    if (key == sf::Keyboard::Scancode::Unknown){return "null";}
    std::string keyStr = sf::Keyboard::getDescription(key);
    for (auto &c : keyStr) {
        c = std::toupper(static_cast<unsigned char>(c));
    }
    return keyStr;
}

bool settingsScene::getIsRecentlyOpen() const {return isRecentlyOpen;}
void settingsScene::setIsRecentlyOpen(bool active) {isRecentlyOpen = active;}
