#include "rankingScene.hpp"

#include <iostream>

rankingScene::rankingScene() {
    load();
}

void rankingScene::update(float delta, game &m_gam) {

}

void rankingScene::draw(sf::RenderWindow &m_win) {

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
    }
}

void rankingScene::save(const stats &p) {
    std::ofstream file("../data/globalstats/stats.txt", std::ios::app);
    std::cout << p.name <<'|'<<p.kills<<'|'<<p.timeAlive<<'\n';
    file << p.name <<'|'<<p.kills<<'|'<<p.timeAlive<<'\n';

}

void rankingScene::createSave() {
    std::ofstream file("../data/globalstats/stats.txt", std::ios::app);
    stats p;
    file << p.name <<'|'<<p.kills<<'|'<<p.timeAlive<<'\n';
}

