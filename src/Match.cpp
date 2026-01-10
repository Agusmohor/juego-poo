#include "Pause.hpp"
#include "Match.hpp"

#include <algorithm>
#include <iostream>

#include "Game.hpp"
#include "Mapa.hpp"
#include <string>

match::match() : m_mapa(), m_ply(), m_zombie() , m_text("../assets/textures/fondo.jpg"), Fondo(m_text), m_hud(), m_trees(10) {
    std::string pngpath ="../assets/textures/map/tiles.png" ; std::string ground = "../assets/textures/map/ground_base.csv"; std::string collision = "../assets/textures/map/ground_collision.csv";
    m_mapa.load(pngpath,ground,collision);
    for (auto &trees : m_trees) {
        float random = (1 + rand()%300);
        float random2 = (1 + rand()%300);
        trees.random();
        trees.setPos({random*2,random2+100});
    }
}


void match::update(float delta,Game &m_gam){
    if (time.getElapsedTime().asSeconds() >= 0.3f) {
        for (auto &tree : m_trees) {
            tree.update();
        }
        time.restart();
    }
    m_ply.getHitboxes(m_trees);
    m_ply.update(delta,m_mapa);


    m_zombie.getPlyPos(m_ply.getPosition());
    m_zombie.update(delta,m_mapa);

    m_hud.update();
    this->doPause(m_gam);
}

void match::updateView(Game &m_gam){
    m_winSize = m_gam.getWinSize();
    m_uiview = m_gam.getUIWinView();
    m_hud.updateView();
}

void match::draw(sf::RenderWindow &m_win){
    this->render(m_win);
    for (auto &trees : m_trees) { trees.draw(m_win); }

    if (timer.getElapsedTime().asSeconds() >= 0.2f) {
        if(attact(m_win,m_zombie.getHitbox())){
            m_zombie.RecieveDamage();
        }
        timer.restart();
    }
    if(m_zombie.isAlive()){
        m_zombie.draw(m_win);
    }

    m_win.setView(m_uiview);
}

void match::doPause(Game &m_gam){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) m_gam.isPaused(true);
}

// dibujo de camara, centrado del hud
// view = camara, win = ventana 
void match::render(sf::RenderWindow &m_win){

    //view mapa centrado en el player
    this->normalView(m_win);

    //se dibuja el mapa
    m_mapa.draw(m_win);
    // m_win.draw(Fondo);

    this->mouseSkin(m_win);
    m_wordlSprites.clear();
    m_wordlSprites.push_back(&m_ply.getSprite());

    for (auto &trees : m_trees) {
        m_wordlSprites.push_back(&trees.getSprite());
    }
    // m_ply.draw(m_win);

    std::sort(m_wordlSprites.begin(),m_wordlSprites.end(),[](sf::Sprite* a, sf::Sprite* b){
        return (a->getPosition().y + a->getGlobalBounds().size.y) <
               (b->getPosition().y + b->getGlobalBounds().size.y);
    });

    for (auto *spr : m_wordlSprites) {
        m_win.draw(*spr);
    }

    // m_ply.drawHitbox(m_win);

    //view de UI
    m_win.setView(m_uiview);

    m_hud.moveHotbar(m_win.mapPixelToCoords(sf::Vector2i(m_uiview.getSize().x,m_uiview.getSize().y )));
    m_hud.draw(m_win);

    //view mapa
    this->normalView(m_win);
}

void match::mouseSkin(const sf::RenderWindow &m_win){
    //si se toca click izq, le manda al player las coords del cursor
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        //mouse getposition(posicion del mouse), mappixel(cambia la pos del mouse a coordenadas en el mundo, para comparar con las coords del player)
        m_ply.updateSkinByMouse(m_win.mapPixelToCoords(sf::Mouse::getPosition(m_win)));
    }
}

void match::normalView(sf::RenderWindow& m_win) {
    m_view.setSize(sf::Vector2f(m_winSize));
    m_view.setCenter(m_ply.getPosition());
    m_view.zoom(0.2);
    m_win.setView(m_view);
}

bool match::attact(sf::RenderWindow &m_win,sf::FloatRect entpos){
    return m_ply.attact(m_win,entpos);
}
