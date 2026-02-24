#include "GameOver.hpp"
#include <iomanip>

#include "Game.hpp"
#include <iostream>


gameover::gameover() : font("../assets/fonts/fuente.ttf"), text(font), text2(font) {
    if (!font.openFromFile("../assets/fonts/fuente.ttf")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_FONT_FROM_FILE");
    shape.setFillColor(sf::Color::Red);
    text.setString("GAME OVER");
    text.setCharacterSize(100);
    text.setPosition({150,150});
}

void gameover::update(float delta, Game &m_gam) {
    if (!isgameover) { m_stats = m_gam.getStats(); isgameover = true; toText();}
}

void gameover::draw(sf::RenderWindow &m_win) {
    m_win.draw(shape);
    m_win.draw(text);
    m_win.draw(text2);
}

void gameover::updateView(Game &m_gam) {

}

void gameover::toText() {
    int totalseg = m_stats.timeAlive;
    int min = totalseg / 60;
    int seg = totalseg % 60;
    std::ostringstream s;
    s << "Kills " << std::to_string(m_stats.kills) << " " << "tiempo vivo " << std::setw(2) << std::setfill('0') << std::to_string(min) << ":" << std::setw(2) << std::setfill('0') << std::to_string(seg);
    text2.setString(s.str());
    text2.setPosition({200,300});
}