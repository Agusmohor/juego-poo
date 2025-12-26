#include "Tree.hpp"
#include <cmath>

tree::tree(): arbol("../assets/textures/arbol.png"),arbol2("../assets/textures/arbolselec.png"),shape(arbol){}
void tree::update(player &m_pl){
    pl_pos=m_pl.getPosition();
    radio.setPosition(shape.getPosition());
    rect=radio.getGlobalBounds();
    if(rect.contains(pl_pos)){
        if(timer.getElapsedTime().asSeconds() >= 0.2f){
            if(shape.getPosition().x > pl_pos.x && shape.getPosition().y<pl_pos.y){
                shape.setPosition({shape.getPosition().x-10.f,shape.getPosition().y+10.f});
            }
            if(shape.getPosition().x > pl_pos.x && shape.getPosition().y > pl_pos.y){
                shape.setPosition({shape.getPosition().x-10.f,shape.getPosition().y-10.f});
            }
            if(shape.getPosition().x < pl_pos.x && shape.getPosition().y > pl_pos.y){
                shape.setPosition({shape.getPosition().x+10.f,shape.getPosition().y+10.f});
            }
        }
    }
}
void tree::draw(sf::RenderWindow &m_win){
    m_win.draw(shape);
}