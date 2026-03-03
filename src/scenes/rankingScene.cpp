#include "scenes/rankingScene.hpp"
#include "core/Game.hpp"

#include <sstream>
#include <algorithm>
#include <iostream>


rankingScene::rankingScene() : backText(font), title(font){
    if(!font.openFromFile("../assets/fonts/MineFont.ttf")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_FONT");
    if(!boton.loadFromFile("../assets/textures/Boton.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");
    if(!botonselec.loadFromFile("../assets/textures/Botonselec.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");
    font.setSmooth(false);

    backButton.setSize({220.f,35.f});
    backButton.setPosition({sf::Vector2f(290,580)});
    title.setString("Ranking");
    title.setCharacterSize(50);
    title.setPosition(sf::Vector2f(290,110));
    backText.setFont(font); backText.setString("Back to main");
    backText.setCharacterSize(20);
    backText.setFillColor(sf::Color::White);
    load(); sortList();
    centerTextToButton(backText,backButton);
}

void rankingScene::update(float delta, game &m_gam) {

}

void rankingScene::showVector(sf::RenderWindow &m_win) {
    float starty=180.f;
    float space=40.f;
    for (int i=0;i<m_list.size();i++) {
        if (i>=10){break;}
        const stats& p = m_list[i];

        int min = p.timeAlive/60;
        int seg = p.timeAlive%60;

        std::ostringstream ss;
        ss << "#" <<i+1 << " " << p.name << "  K:" << p.kills << "  T:"<<std::setw(2)<<std::setfill('0')<<min<<":"<<std::setw(2)<<std::setfill('0')<<seg;

        sf::Text text(font,ss.str());
        text.setCharacterSize(20);
        text.setPosition({300,starty + i*space});
        if (i==0){text.setFillColor({255,255,153});}
        if (i==1){text.setFillColor({255,204,102});}
        if (i==2){text.setFillColor({255,153,51});}
        m_win.draw(text);
    }
}

void rankingScene::draw(sf::RenderWindow &m_win) {
    button_overlay(m_win,backButton,botonselec,boton);
    m_win.draw(backButton);
    m_win.draw(backText);
    m_win.draw(title);
    showVector(m_win);
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
        aux.timeAlive = std::stof(line.substr(pos2+1));
        m_list.push_back(aux);
    }
    sortList();
    file.close();
    updateList();
}

void rankingScene::save(const stats &p) {
    std::ofstream file("../data/globalstats/stats.txt", std::ios::app);
    file << p.name <<'|'<<p.kills<<'|'<<p.timeAlive<<'\n';

}

void rankingScene::createSave() {
    std::ofstream file("../data/globalstats/stats.txt", std::ios::app);
}

void rankingScene::ProcessEvent(game &game, sf::Event &event) {
    if (const auto* evt = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (evt->button == sf::Mouse::Button::Left) {
            auto &win = game.getWindow();
            if (mouseOver(win,backButton)) {buttonPressed(type::back);}
        }
    }
}

void rankingScene::buttonPressed(type t) {
    switch (t) {
        case type::back : backmain = true; break;
    }
}

bool rankingScene::getBackRequest() const {
    return backmain;
}

void rankingScene::setBackRequest(bool back) {backmain = back;}

void rankingScene::updateList() {
    std::ofstream file("../data/globalstats/stats.txt", std::ios::trunc);
    if (m_list.empty()) { return;}
    if (m_list.size() > 10){m_list.resize(10);}
    for (auto &p : m_list) {
        file << p.name <<'|'<<p.kills<<'|'<<p.timeAlive<<'\n';
    }
}
