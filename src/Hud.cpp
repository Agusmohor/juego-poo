#include "Hud.hpp"

hud::hud() : hobTexture("../assets/textures/entity/player/gui/entire_hotbar.png"), hotbarBar(hobTexture), hselTe("../assets/textures/entity/player/gui/selected.png"),hsel(hselTe) {
    if(!hselTe.loadFromFile("../assets/textures/entity/player/gui/selected.png")) throw std::runtime_error("error al cargar hud");
    hotbarBar.setOrigin(sf::Vector2f(48,16));
    hotbarBar.setScale(sf::Vector2f(4,4));
    hsel.setOrigin(sf::Vector2f(8,16)); hsel.setScale(sf::Vector2f(4,4));
    hsel.setPosition(sf::Vector2f(240,798));
    // hotbarBar.setTextureRect(sf::IntRect({0,0},{16,16}));
    hotbarBar.setPosition(sf::Vector2f(400,798));
}

void hud::draw(sf::RenderWindow &m_win){
    m_win.draw(hotbarBar);
    m_win.draw(hsel);
}

void hud::update(){

}