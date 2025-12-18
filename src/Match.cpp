#include "Pause.hpp"
#include "Match.hpp"
#include "Game.hpp"

match::match() : m_ply() , m_text("../assets/textures/fondo.jpg"), Fondo(m_text), m_hud() {}


void match::update(Game &m_gam){
    m_ply.update();
    m_hud.update();
    match::doPause(m_gam);
    m_winSize = m_gam.getWinSize();
    m_uiview = m_gam.getUIWinView();
}

void match::draw(sf::RenderWindow &m_win){
    match::render(m_win);

}

void match::doPause(Game &m_gam){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) m_gam.isPaused(true);
}

// dibujo de camara, centrado del hud
// view = camara, win = ventana 
void match::render(sf::RenderWindow &m_win){
    m_view.setSize(sf::Vector2f(m_winSize));
    m_view.setCenter(m_ply.getPosition());
    m_win.setView(m_view);
    m_win.draw(Fondo);
    match::mouseSkin(m_win);
    m_ply.draw(m_win);

    m_win.setView(m_uiview);
    m_hud.draw(m_win);
}

void match::mouseSkin(sf::RenderWindow &m_win){
    //si se toca click izq, le manda al player las coords del cursor
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        //mouse getposition(posicion del mouse), mappixel(cambia la pos del mouse a coordenadas en el mundo, para comparar con las coords del player)
        m_ply.updateSkinByMouse(m_win.mapPixelToCoords(sf::Mouse::getPosition(m_win)));
    }
}