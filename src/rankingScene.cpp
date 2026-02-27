#include "rankingScene.hpp"

#include <iostream>

rankingScene::rankingScene() {

}

void rankingScene::update(float delta, game &m_gam) {

}

void rankingScene::draw(sf::RenderWindow &m_win) {

}

void rankingScene::load() {
    std::ifstream file("../data/globalstats/stats.txt");
    if (!file.is_open()) {createSave();}
    stats aux;
    std::string line;
    while (std::getline(file, line)) {
        int pos = line.find('|') + 1;
        int pos2 = line.find('|',pos);
        aux.name = line.substr(0,line.find('|'));
        aux.kills = std::stoi(line.substr(pos,pos2 - pos));
        aux.timeAlive = std::stof(line.substr(pos2-1));
    }
    std::cout << aux.name << " " << aux.kills << " " << aux.timeAlive << std::endl;
}

void rankingScene::save(const stats &p) {
    std::ofstream file("../data/globalstats/stats.txt", std::ios::app);


    file << p.name <<'|'<<p.kills<<'|'<<p.timeAlive<<'\n';

}

void rankingScene::createSave() {
    std::ofstream file("../data/globalstats/stats.txt");
    stats p;
    file << p.name <<'|'<<p.kills<<'|'<<p.timeAlive<<'\n';
}