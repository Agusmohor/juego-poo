#include "Pause.hpp"

PauseScene::PauseScene():m_font("../assets/fonts/fuente.ttf"),m_text(m_font,"Pause"){
    m_text.setCharacterSize(100);
    sf::Vector2f v(300,400);
    m_text.setPosition(v);
}

void PauseScene::update(Game &m_gam){
    PauseScene::backMatch(m_gam);
}

void PauseScene::backMatch(Game &m_gam){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) m_gam.isPaused(false);
}

void PauseScene::draw(sf::RenderWindow &m_win){
    m_win.draw(m_text);
}