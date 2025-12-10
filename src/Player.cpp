#include "Player.hpp"

player::player() : m_txt("../assets/textures/prueba.png"), m_spr(m_txt) {
    if(!m_txt.loadFromFile("../assets/textures/prueba.png")) throw std::runtime_error("err");
    m_spr.setTexture(m_txt);
    sf::Vector2f scl(10.f,10.f);
    m_spr.setScale(scl);
    m_spr.setPosition({300,300});
    speed = 10;
    dir.x = 0.f; dir.y = 0.f;
}

void player::draw(sf::RenderWindow& m_win){
    m_win.draw(m_spr);
    player::viewCentre(m_win);
}

void player::m_key(){
    dir.x = 0.f; dir.y = 0.f;
    //interaccion teclas
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) dir.y = -1.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) dir.x = -1.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) dir.y = 1.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) dir.x = 1.f;
}

void player::m_mouse(){
    //interaccion mouse
}
void player::viewCentre(sf::RenderWindow &m_win){
    m_view.setCenter(pl_pos);
    m_win.setView(m_view);

}
void player::update(){
    //actualizar player
    player::m_key();
    m_spr.move(dir*speed);
    player::m_mouse();
    pl_pos=m_spr.getPosition();
}

