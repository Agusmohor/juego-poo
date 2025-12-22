#include "Mapa.h"
#include <fstream>


mapa::mapa(){}

csv mapa::loadCsv(const std::string &path) {
    std::ifstream file(path); if (!file.is_open()) throw std::runtime_error("error al cargar el csv");

    csv layer;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string cell; int rowWidth = 0;

        while (getline(ss, cell, ',')) {
            if (!cell.empty() && cell.back() == '\r') cell.pop_back();

            int value = std::stoi(cell);

            layer.tiles.push_back(value);
            rowWidth++;
        }
        if (layer.w == 0) layer.w = rowWidth;
        layer.h++;
    }
    return layer;
}

void mapa::load(std::string &texturePath, std::string &groundCSV) {
    if (!m_tileTexture.loadFromFile(texturePath)) throw std::runtime_error("error al cargar el texture");
    m_tileTexture.setSmooth(false);
    m_ground = loadCsv(groundCSV);
}

void mapa::draw(sf::RenderWindow& m_win) {
    sf::Sprite sprite(m_tileTexture);

    int columns = m_tileTexture.getSize().x / m_tilesize;
    for (int y = 0; y < m_ground.h; y++) {
        for (int x = 0; x < m_ground.w; x++) {
            int id = m_ground.tiles[y * m_ground.w + x];
            if (id < 0) continue;

            int tx = (id % columns) * m_tilesize;
            int ty = (id / columns) * m_tilesize;

            sprite.setTextureRect(sf::IntRect({tx,ty},{m_tilesize, m_tilesize}));
            sprite.setPosition(sf::Vector2f(x*m_tilesize,y*m_tilesize));

            m_win.draw(sprite);
        }
    }
}
