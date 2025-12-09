#include "Hud.hpp"

hud::hud() : hobTexture("../assets/textures/entity/player/gui/hotbar.png"), hotbarBar(hobTexture) {
    if(!hobTexture.loadFromFile("../assets/textures/entity/player/gui/hotbar.png")) throw std::runtime_error("error al cargar hud");
    hotbarBar.setScale(sf::Vector2f(3,3));
    hotbarBar.setPosition(sf::Vector2f(400,750));
    hotbarBar.setTextureRect(sf::IntRect({0,0},{16,16}));
}

void hud::draw(sf::RenderWindow &m_win){
    m_win.draw(hotbarBar);
}

void hud::update(){

}