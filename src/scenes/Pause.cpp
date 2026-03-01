#include "scenes/Pause.hpp"
#include <iostream>
#include <scenes/settingsScene.hpp>

PauseScene::PauseScene():m_text(m_font,"Pause"), resumeText(m_font,""), settingText(m_font,""), exitText(m_font,""){
    if (!m_font.openFromFile("../assets/fonts/MineFont.ttf")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_FONT");
    if(!boton.loadFromFile("../assets/textures/Boton.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");
    if(!botonselec.loadFromFile("../assets/textures/Botonselec.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");

    m_font.setSmooth(false);

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

    setting = resume; setting.setPosition({resume.getPosition().x,resume.getPosition().y+45});
    exit_button = resume; exit_button.setPosition({setting.getPosition().x,setting.getPosition().y+45});
    settingText = resumeText; settingText.setString("Settings"); settingText.setPosition({resumeText.getPosition().x,resumeText.getPosition().y+45});
    exitText = resumeText; exitText.setString("Save and Quit"); exitText.setPosition({resumeText.getPosition().x-25,settingText.getPosition().y+45});
    centerTextToButton(resumeText,resume);
    centerTextToButton(settingText,setting);
    centerTextToButton(exitText,exit_button);
    settingScene;
}

void PauseScene::update(float delta,game &m_gam){
    // backMatch(m_gam);
    settingScene.update(delta,m_gam);
    if (settingScene.getExit()) {isSettings = false; settingScene.setExit(false);}
    if (isExit) {
        m_gam.setSaveAndQuit(true);
        m_gam.delPause();
    }

}

void PauseScene::updateView(game &m_gam){}

void PauseScene::ProcessEvent(game &game, sf::Event &event) {
    if (isSettings) {settingScene.ProcessEvent(game,event); return;}
    if (((event.is<sf::Event::KeyPressed>() && event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) || isResume) && !isSettings) {
        game.delPause();
    }
    auto& win = game.getWindow();
    if (const auto* evt = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (evt->button == sf::Mouse::Button::Left) {
            if (mouseOver(win,resume)){buttonPressed(type::resume);}
            if (mouseOver(win,exit_button)){buttonPressed(type::mainmenu);}
            if (mouseOver(win,setting)){buttonPressed(type::setting);}
        }
    }
}

void PauseScene::draw(sf::RenderWindow &m_win){
    if (!isSettings) {drawPause(m_win);} else {settingScene.draw(m_win);}
}

void PauseScene::drawPause(sf::RenderWindow &m_win) {
    button_overlay(m_win,resume,type::resume,botonselec,boton);
    button_overlay(m_win,exit_button,type::mainmenu,botonselec,boton);
    button_overlay(m_win,setting,type::setting,botonselec,boton);
    m_win.draw(overlay);
    m_win.draw(m_text);
    m_win.draw(resume);
    m_win.draw(resumeText);
    m_win.draw(exit_button);
    m_win.draw(setting);
    m_win.draw(exitText);
    m_win.draw(settingText);
}


//s
void PauseScene::buttonPressed( type t) {
    switch(t) {
        case type::resume: isResume = true; break;
        case type::setting : isSettings = true; break;
        case type::mainmenu : isExit = true; break;
    }
}

