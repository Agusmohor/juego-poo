#include "Pause.hpp"
#include <iostream>
#include <settingsScene.hpp>

PauseScene::PauseScene():m_text(m_font,"Pause"), resumeText(m_font,""), settingText(m_font,""), exitText(m_font,""){
    if (!m_font.openFromFile("../assets/fonts/MineFont.ttf")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_FONT");
    if(!boton.loadFromFile("../assets/textures/Boton.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");
    if(!botonselec.loadFromFile("../assets/textures/Botonselec.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");

    m_text.setFont(m_font);
    m_text.setCharacterSize(70);
    m_text.setPosition(sf::Vector2f(300,150));
    overlay.setSize({6000.f,6000.f});
    overlay.setFillColor(sf::Color(0,0,0,170));
    overlay.setPosition(sf::Vector2f(-2000,-2000));

    resume.setSize({220.f,35.f});
    resume.setPosition({sf::Vector2f(290,520)});

    resumeText.setFont(m_font); resumeText.setString("Resume");
    resumeText.setCharacterSize(20);
    resumeText.setFillColor(sf::Color::White);
    resumeText.setPosition(sf::Vector2f(350,540));

    setting = resume; setting.setPosition({resume.getPosition().x,resume.getPosition().y+45});
    exit_button = resume; exit_button.setPosition({setting.getPosition().x,setting.getPosition().y+45});
    settingText = resumeText; settingText.setString("Settings"); settingText.setPosition({resumeText.getPosition().x,resumeText.getPosition().y+45});
    exitText = resumeText; exitText.setString("Exit"); exitText.setPosition({resumeText.getPosition().x+30,settingText.getPosition().y+45});

    settingScene;
}

void PauseScene::update(float delta,Game &m_gam){
    // backMatch(m_gam);
    settingScene.update(delta,m_gam);
    if (settingScene.getExit()) {isSettings = false; settingScene.setExit(false);}

}

void PauseScene::updateView(Game &m_gam){}

void PauseScene::ProcessEvent(Game &game, sf::Event &event) {
    if (isSettings) settingScene.ProcessEvent(game,event);
    if (((event.is<sf::Event::KeyPressed>() && event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) || isResume) && !isSettings) {
        game.delPause();
    }
    if (const auto* evt = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (evt->button == sf::Mouse::Button::Left) {lbuttonpressed = true;}
    }else{lbuttonpressed = false;}
}

// void PauseScene::backMatch(Game &m_gam){
//     if((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || isResume) && !isSettings) m_gam.isPaused(false);
// }

void PauseScene::draw(sf::RenderWindow &m_win){
    if (!isSettings) {drawPause(m_win);} else {settingScene.draw(m_win);}
}

void PauseScene::drawPause(sf::RenderWindow &m_win) {
    button_overlay(m_win,resume,type::resume);
    button_overlay(m_win,exit_button,type::exit);
    button_overlay(m_win,setting,type::setting);
    m_win.draw(overlay);
    m_win.draw(m_text);
    m_win.draw(resume);
    m_win.draw(resumeText);
    m_win.draw(exit_button);
    m_win.draw(setting);
    m_win.draw(exitText);
    m_win.draw(settingText);
}


void PauseScene::button_overlay(const sf::RenderWindow &win, sf::RectangleShape &button, type t){
    sf::Vector2i mouse_pos(sf::Mouse::getPosition(win).x,sf::Mouse::getPosition(win).y);
    sf::Vector2f window_pos = win.mapPixelToCoords(mouse_pos);

    if (button.getGlobalBounds().contains(window_pos)) {
        button.setTexture(&botonselec);
        if (lbuttonpressed) {
            switch(t) {
                case type::resume : isResume = true; break;
                case type::setting : isSettings = true; settingScene.setIsRecentlyOpen(true); break;
                case type::exit : isExit = true; break;
                    default: lbuttonpressed = false; break;
            }
        }
    }else{
        button.setTexture(&boton);
    }
}


