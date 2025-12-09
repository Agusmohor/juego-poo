#include "Pause.hpp"
#include "Game.hpp"
#include "Match.hpp"

pause::pause():m_font("../assets/fonts/fuente.ttf"),m_text(m_font,"Pause"){
    m_text.setCharacterSize(100);
    sf::Vector2f v(300,400);
    m_text.setPosition(v);
}
void pause::update(Game &m_gam){
    if (timer.getElapsedTime().asSeconds() >= 0.1f) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) m_gam.setScene(new match);
        timer.restart();
    }
}
void pause::draw(sf::RenderWindow &m_win){
    m_win.clear(sf::Color::Black);
    m_win.draw(m_text);
}