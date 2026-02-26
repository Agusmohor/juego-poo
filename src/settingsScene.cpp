#include "settingsScene.hpp"

settingsScene::settingsScene() {
    if(!boton.loadFromFile("../assets/textures/Boton.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");
    if(!botonselec.loadFromFile("../assets/textures/Botonselec.png")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_BOTON_TEXTURE_FROM_FILE");

    background.setSize({6000.f,6000.f});
    background.setFillColor(sf::Color(0,0,0,210));
    background.setPosition(sf::Vector2f(-2000,-2000));

    Ab1.setSize({50.f,50.f});
    Ab1.setPosition({200.f,200.f});
}

void settingsScene::update(float delta,Game &m_game) {

}

void settingsScene::draw(sf::RenderWindow &m_win) {
    button_overlay(m_win,Ab1,type::Ab1);
    m_win.draw(background);
    m_win.draw(Ab1);
}

void settingsScene::updateView(Game &m_gam) {

}

void settingsScene::button_overlay(const sf::RenderWindow &win, sf::RectangleShape &button, type t){
    sf::Vector2i mouse_pos(sf::Mouse::getPosition(win).x,sf::Mouse::getPosition(win).y);
    sf::Vector2f window_pos = win.mapPixelToCoords(mouse_pos);

    if (button.getGlobalBounds().contains(window_pos)) {
        button.setTexture(&botonselec);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            switch(t) {

            }
        }
    }else{
        button.setTexture(&boton);
    }
}

