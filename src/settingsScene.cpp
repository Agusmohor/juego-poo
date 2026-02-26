#include "settingsScene.hpp"

#include <iostream>

settingsScene::settingsScene() : ab1Text(font), ab2Text(font), ab3Text(font), ab4Text(font), exitText(font) {
    if (!font.openFromFile("../assets/fonts/MineFont.ttf")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_FONT_FROM_FILE");
    if(!boton.loadFromFile("../assets/textures/Boton.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");
    if(!botonselec.loadFromFile("../assets/textures/Botonselec.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");

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
    exit.setSize({220.f,35.f});
    exit.setPosition({sf::Vector2f(290,610)});

    exitText.setFont(font); exitText.setString("Exit");
    exitText.setCharacterSize(20);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(sf::Vector2f(380,630));
}

void settingsScene::update(float delta,Game &m_game) {

}

void settingsScene::draw(sf::RenderWindow &m_win) {
    button_overlay(m_win,Ab1,type::Ab1);
    button_overlay(m_win,Ab2,type::Ab2);
    button_overlay(m_win,Ab3,type::Ab3);
    button_overlay(m_win,Ab4,type::Ab4);
    button_overlay(m_win,exit,type::exit);
    m_win.draw(background);
    m_win.draw(Ab1);
    m_win.draw(Ab2);
    m_win.draw(Ab3);
    m_win.draw(Ab4);
    m_win.draw(exit);
    m_win.draw(ab1Text);
    m_win.draw(ab2Text);
    m_win.draw(ab3Text);
    m_win.draw(ab4Text);
    m_win.draw(exitText);

}

void settingsScene::updateView(Game &m_gam) {

}

void settingsScene::button_overlay(const sf::RenderWindow &win, sf::RectangleShape &button, type t){
    sf::Vector2i mouse_pos(sf::Mouse::getPosition(win).x,sf::Mouse::getPosition(win).y);
    sf::Vector2f window_pos = win.mapPixelToCoords(mouse_pos);

    if (button.getGlobalBounds().contains(window_pos)) {
        button.setTexture(&botonselec);
        if (lbuttonpressed) {
            switch(t) {
                case type::Ab1 : curraction = action::shield; waitingForKey = true; break;
                case type::Ab2 : curraction = action::dash;waitingForKey = true; break;
                case type::Ab3 : curraction = action::fire;waitingForKey = true; break;
                case type::Ab4 : curraction = action::heal;waitingForKey = true; break;
                case type::exit : isexit = true; break;
            }
        }
    }else{
        button.setTexture(&boton);
    }
}

void settingsScene::setKey(sf::Keyboard::Key key) {
    m_keys[static_cast<int>(curraction)] = key;
}

void settingsScene::ProcessEvent(Game &game, sf::Event &event) {
    if (const auto* evt = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (evt->button == sf::Mouse::Button::Left) {lbuttonpressed = true;}
    }else{lbuttonpressed = false;}
    if (const auto* evt = event.getIf<sf::Event::KeyPressed>()) {
        if (waitingForKey) {
            if (evt->code == sf::Keyboard::Key::Escape) {waitingForKey = false; return;;}
            setKey(evt->code);
            waitingForKey = false;
        }
    }
}

const std::array<sf::Keyboard::Key,4>& settingsScene::getKeys() { return m_keys; }

bool settingsScene::isWaitingForKey() const {return waitingForKey;}

bool settingsScene::getExit() const { return isexit; }
void settingsScene::setExit(bool exit) { isexit = exit; }
