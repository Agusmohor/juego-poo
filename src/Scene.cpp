#include "Scene.hpp"

void scene::button_overlay(const sf::RenderWindow &win, sf::RectangleShape &button, type t, sf::Texture &botonSelec, sf::Texture &buton) {
    sf::Vector2i mouse_pos(sf::Mouse::getPosition(win).x,sf::Mouse::getPosition(win).y);
    sf::Vector2f window_pos = win.mapPixelToCoords(mouse_pos);

    if (button.getGlobalBounds().contains(window_pos)) {
        button.setTexture(&botonSelec);
    }else{
        button.setTexture(&buton);
    }
}

bool scene::clickOn(const sf::RenderWindow &win, const sf::RectangleShape &btn) {
    auto mp = sf::Mouse::getPosition(win);
    auto wp = win.mapPixelToCoords(mp);
    return btn.getGlobalBounds().contains(wp);
}