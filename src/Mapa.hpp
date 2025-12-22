#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

struct csv {
    int w = 0;
    int h = 0;
    std::vector<int> tiles;
};

class mapa {
    int m_tilesize = 32;

    csv loadCsv(const std::string& path);

    sf::Texture m_tileTexture;
    csv m_ground;

public:
    mapa();

    void load(std::string& texturePath, std::string& groundCSV);

    void draw(sf::RenderWindow& m_win);


};

