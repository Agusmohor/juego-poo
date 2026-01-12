#include "Pause.hpp"
#include "Match.hpp"

#include <algorithm>
#include <iostream>

#include "Game.hpp"
#include "Mapa.hpp"
#include <string>

match::match() : m_mapa(),  m_zombie() , m_text("../assets/textures/fondo.jpg"), Fondo(m_text), m_hud() {
    std::string pngpath ="../assets/textures/map/tiles.png" ; std::string ground = "../assets/textures/map/ground_base.csv"; std::string collision = "../assets/textures/map/ground_collision.csv";
    std::string grass = "../assets/textures/map/ground_grass.csv";

    m_mapa.load(pngpath,ground,grass,collision);

    m_ply = std::make_unique<player>();

    for (size_t i=0;i<100;i++) {
        m_obtacles.push_back(std::make_unique<tree>());
    }
    for (auto &trees : m_obtacles) {
        float random = (1 + rand()%300);
        float random2 = (1 + rand()%300);
        trees->random();
        trees->setPos({random*2 + 380,random2+100});
    }
}


void match::update(float delta,Game &m_gam){
    if (time.getElapsedTime().asSeconds() >= 0.1f) {
        for (auto &tree : m_obtacles) {
            tree->update();
        }
         m_ply->updateTexture();
        m_zombie.updateTexture();
        time.restart();
    }
    //actualizado de hitbox obstaculos
    m_hitboxes.clear();
    for (auto &box : m_obtacles) {
        m_hitboxes.push_back(box->getHitbox());
    }

    //update del player si esta vivo
    if (m_ply->isAlive()) {m_ply->setHitboxes(m_hitboxes);m_ply->update(delta,m_mapa);} m_zombie.setHitboxes(m_hitboxes);
    //si no esta vivo, y presiona enter, crea otro personaje :)
    if (!m_ply->isAlive() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
        m_ply.reset(); m_ply = std::make_unique<player>();
    }



    if (m_ply->isAlive()) m_zombie.getPlyPos(m_ply->getPosition());
    m_zombie.update(delta,m_mapa);

    m_hud.update();
    m_hud.checkhp(m_ply->getHealth());
    this->doPause(m_gam);
}

void match::updateView(Game &m_gam){
    m_winSize = m_gam.getWinSize();
    m_uiview = m_gam.getUIWinView();
    m_hud.updateView();
}

void match::draw(sf::RenderWindow &m_win){
    this->render(m_win);

    if (timer.getElapsedTime().asSeconds() >= 0.2f) {
        if(attact(m_win,m_zombie.getHitbox())){
            m_zombie.RecieveDamage();
        }
        timer.restart();
    }
    // if(m_zombie.isAlive()){
    //     m_zombie.draw(m_win);
    // }

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
    m_wordlSprites.push_back(&m_ply->getSprite());
    m_wordlSprites.push_back(&m_zombie.getSprite());
    for (auto &trees : m_obtacles) {
        m_wordlSprites.push_back(&trees->getSprite());
    }

    std::sort(m_wordlSprites.begin(),m_wordlSprites.end(),[](sf::Sprite* a, sf::Sprite* b){
        return (a->getPosition().y + a->getGlobalBounds().size.y) <
               (b->getPosition().y + b->getGlobalBounds().size.y);
    });

    m_ply->draw(m_win);m_zombie.draw(m_win);
    for (auto *spr : m_wordlSprites) {
            m_win.draw(*spr);

    }
    // m_ply.drawHitbox(m_win);
    // m_zombie.drawHitbox(m_win);

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
        m_ply->updateSkinByMouse(m_win.mapPixelToCoords(sf::Mouse::getPosition(m_win)));
    }
}

void match::normalView(sf::RenderWindow& m_win) {
    m_view.setSize(sf::Vector2f(m_winSize));
    m_view.setCenter(m_ply->getPosition());
    m_view.zoom(0.2);
    m_win.setView(m_view);
}

bool match::attact(sf::RenderWindow &m_win,sf::FloatRect entpos){
    return m_ply->attact(m_win,entpos);
}
