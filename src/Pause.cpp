#include "Pause.hpp"

PauseScene::PauseScene():m_font("../assets/fonts/fuente.ttf"),m_text(m_font,"Pause"){
    m_text.setCharacterSize(100);
    m_text.setPosition(sf::Vector2f(300,150));
    overlay.setSize({6000.f,6000.f});
    overlay.setFillColor(sf::Color(0,0,0,170));
}

void PauseScene::update(float delta,Game &m_gam){
    this->backMatch(m_gam);
}

void PauseScene::updateView(Game &m_gam){}

void PauseScene::backMatch(Game &m_gam){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) m_gam.isPaused(false);
}

void PauseScene::draw(sf::RenderWindow &m_win){
    overlay.setPosition(sf::Vector2f(-2000,-2000));
    m_win.draw(overlay);
    m_win.draw(m_text);
}

