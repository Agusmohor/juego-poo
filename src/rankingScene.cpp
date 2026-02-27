#include "rankingScene.hpp"

#include <algorithm>
#include <iostream>

#include "Game.hpp"

rankingScene::rankingScene() : backText(font) {
    if(!font.openFromFile("../assets/fonts/MineFont.ttf")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_FONT");
    if(!boton.loadFromFile("../assets/textures/Boton.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");
    if(!botonselec.loadFromFile("../assets/textures/Botonselec.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");

    backButton.setSize({220.f,35.f});
    backButton.setPosition({sf::Vector2f(290,520)});
    backText.setFont(font); backText.setString("Back to main");
    backText.setCharacterSize(20);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(sf::Vector2f(330,538));
    load(); sortList();
}

void rankingScene::update(float delta, game &m_gam) {

}

void rankingScene::draw(sf::RenderWindow &m_win) {
    button_overlay(m_win,backButton,type::back,botonselec,boton);
    m_win.draw(backButton);
    m_win.draw(backText);
}

void rankingScene::sortList() {
    if (m_list.empty()) {return;}
    std::sort(m_list.begin(),m_list.end(),[](const stats& a, const stats& b) {
        if (a.kills != b.kills) {return a.kills > b.kills;}
        return a.timeAlive > b.timeAlive;
    });
}

void rankingScene::load() {
    std::ifstream file("../data/globalstats/stats.txt");
    if (!file.is_open()) {createSave(); return;}
    stats aux;
    std::string line;
    m_list.clear();
    while (std::getline(file, line)) {
        int pos = line.find('|');
        int pos2 = line.find('|',pos + 1);
        if (pos == std::string::npos || pos2 == std::string::npos) {continue;}
        aux.name = line.substr(0,line.find('|'));
        aux.kills = std::stoi(line.substr(pos+1,pos2 - pos));
        aux.timeAlive = std::stof(line.substr(pos2-1));
        file.ignore();
        m_list.push_back(aux);
    }
}

void rankingScene::save(const stats &p) {
    std::ofstream file("../data/globalstats/stats.txt", std::ios::app);
    std::cout << p.name <<'|'<<p.kills<<'|'<<p.timeAlive<<'\n';
    file << p.name <<'|'<<p.kills<<'|'<<p.timeAlive<<'\n';

}

void rankingScene::createSave() {
    std::ofstream file("../data/globalstats/stats.txt", std::ios::app);
}

void rankingScene::ProcessEvent(game &game, sf::Event &event) {
    if (const auto* evt = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (evt->button == sf::Mouse::Button::Left) {
            auto &win = game.getWindow();
            if (clickOn(win,backButton)) {buttonPressed(type::back);}
        }
    }
}

void rankingScene::buttonPressed(type t) {
    switch (t) {
        case type::back : backmain = true; break;
    }
}

bool rankingScene::getBackRequest() {
    return backmain;
}

void rankingScene::setBackRequest(bool back) {backmain = back;}