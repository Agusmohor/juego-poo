#include "Pause.hpp"
#include "Match.hpp"
#include "Game.hpp"
#include <string>

match::match() : m_mapa(), m_ply(), m_zombie() , m_text("../assets/textures/fondo.jpg"), Fondo(m_text), m_hud() {
    std::string pngpath ="../assets/textures/map/Sprite-0001.png" ; std::string ground = "../assets/textures/map/ground";
    m_mapa.load(pngpath,ground);
}


void match::update(Game &m_gam){
    m_ply.update();
    m_hud.update();
    this->doPause(m_gam);
    m_zombie.getPlyPos(m_ply.getPosition());
    m_zombie.update();
}

void match::updateView(Game &m_gam){
    m_winSize = m_gam.getWinSize();
    m_uiview = m_gam.getUIWinView();
    m_hud.updateView();
}

void match::draw(sf::RenderWindow &m_win){
    this->render(m_win);
    m_zombie.draw(m_win);

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
    m_ply.draw(m_win);

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
    m_view.zoom(0.5);
    m_win.setView(m_view);
}
