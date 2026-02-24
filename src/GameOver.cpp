#include "GameOver.hpp"

#include "Game.hpp"
#include <iostream>

sStats::sStats(const sf::Font& t) : kills(t), time(t){}

gameover::gameover() : font("../assets/fonts/fuente.ttf"), text(font), m_stats2(font) {
    if (!font.openFromFile("../assets/fonts/fuente.ttf")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_FONT_FROM_FILE");
    shape.setFillColor(sf::Color::Red);
    text.setString("GAME OVER");
    text.setCharacterSize(100);
    text.setPosition({160,150});
}

void gameover::update(float delta, Game &m_gam) {
    if (!isgameover) { m_stats = m_gam.getStats(); isgameover = true; toText();}
}

void gameover::draw(sf::RenderWindow &m_win) {
    m_win.draw(shape);
    m_win.draw(text);
    m_win.draw(m_stats2.kills);
    m_win.draw(m_stats2.time);
}

void gameover::updateView(Game &m_gam) {

}

void gameover::toText() {
    m_stats2.kills.setString(std::to_string(m_stats.kills)) ;
    m_stats2.time.setString(std::to_string(m_stats.timeAlive)) ;

    m_stats2.kills.setPosition({160,100});
    m_stats2.time.setPosition({200,100});
}