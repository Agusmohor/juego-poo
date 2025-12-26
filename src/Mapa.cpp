#include "Mapa.hpp"
#include <cmath>
#include <fstream>
#include<iostream>


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

void mapa::load(std::string &texturePath, std::string &groundCSV, std::string &collisionCSV) {
    if (!m_tileTexture.loadFromFile(texturePath)) throw std::runtime_error("error al cargar el texture");
    m_tileTexture.setSmooth(false);
    m_ground = loadCsv(groundCSV);
    m_collision = loadCsv(collisionCSV);
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


<<<<<<< HEAD
bool mapa::isSolidTile(int tx, int ty) const {
    // 1. Validar bordes izquierdos y superiores (coordenadas < 0)
    // Si tx o ty son negativos, el personaje está en la zona negra.
    if (tx < 0 || ty < 0) return true;

    // 2. Validar bordes derechos e inferiores
    if (tx >= m_collision.w || ty >= m_collision.h) return true;

    // 3. Obtener el ID del tile si está dentro del mapa
    int id = m_collision.tiles[ty * m_collision.w + tx];
    
    // Si el ID es 0 o más, es un obstáculo (como el agua ID: 9)
    return id >= 0;
}
=======
>>>>>>> 83c89af86b051c1721d51c3616d1f48511b628d9

