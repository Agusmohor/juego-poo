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
    int tilesize = 32;

    csv loadCsv(const std::string& path);
    void drawCSV(sf::RenderWindow &m_win, csv &m_csv, sf::Texture &texture, int tsize);

    sf::Texture m_tileTexture;
    csv m_ground,m_grass;

    std::vector<sf::FloatRect> m_colliders;

public:

    void load(std::string& texturePath, std::string& groundCSV, std::string& grassCSV);
    void draw(sf::RenderWindow& m_win);

};

