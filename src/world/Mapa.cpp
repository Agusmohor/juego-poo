#include "world/Mapa.hpp"
#include <fstream>



csv mapa::loadCsv(const std::string &path) {
    std::ifstream file(path); if (!file.is_open()) throw std::runtime_error("ERROR:COULD_NOT_OPEN_CSV_FILE");
    
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

void mapa::load(std::string &texturePath, std::string &groundCSV, std::string &grassCSV) {
    if (!m_tileTexture.loadFromFile(texturePath)) throw std::runtime_error("ERROR:COULD_NOT_LOAD_TEXTURE_FROM_FILE");
    m_tileTexture.setSmooth(false);
    m_ground = loadCsv(groundCSV);
    m_grass = loadCsv(grassCSV);
}

void mapa::draw(sf::RenderWindow& m_win) {
    drawCSV(m_win,m_ground,m_tileTexture,tilesize);
    drawCSV(m_win,m_grass,m_tileTexture,tilesize);
}

void mapa::drawCSV(sf::RenderWindow& m_win, csv &m_csv, sf::Texture &texture, int tsize) {
    sf::Sprite sprite(texture);

    int columns = m_tileTexture.getSize().x / tsize;
    for (int y = 0; y < m_csv.h; y++) {
        for (int x = 0; x < m_csv.w; x++) {
            int id = m_csv.tiles[y * m_csv.w + x];
            if (id < 0) continue;

            int tx = (id % columns) * tsize;
            int ty = (id / columns) * tsize;

            sprite.setTextureRect(sf::IntRect({tx,ty},{tsize, tsize}));
            sprite.setPosition(sf::Vector2f(x*tsize,y*tsize));

            m_win.draw(sprite);
        }
    }
}