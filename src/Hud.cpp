#include "Hud.hpp"
#include <iostream>

#include "Player.hpp"

hud::hud() : hobTexture("../assets/textures/entity/player/gui/gui.png"), hotbar(hobTexture),hsel(hobTexture), overS(hobTexture), life(hobTexture),font("../assets/fonts/MineFont.ttf"), text(font,""), playerHp(5){

    if(!hselTe.loadFromFile("../assets/textures/entity/player/gui/selected.png")) throw std::runtime_error("ERROR:COULD_NOT_OPEN_HUD_TEXTURE_FROM_FILE");

    k_1 = sf::Keyboard::Key::Num1;k_2 = sf::Keyboard::Key::Num2;k_3 = sf::Keyboard::Key::Num3;
    k_4 = sf::Keyboard::Key::Num4;k_5 = sf::Keyboard::Key::Num5;k_6 = sf::Keyboard::Key::Num6;

    size = sf::Vector2i(16,16);
    hotbar.setTextureRect({{20,20},{size}}); scale = sf::Vector2f(4,4);
    hotbar.setOrigin(sf::Vector2f(48,16)); hotbar.setScale(sf::Vector2f(scale));
    hotbar.setPosition(sf::Vector2f(400,798));

    hsel.setTextureRect({{182,128},{size}});
    hsel.setOrigin(sf::Vector2f(48,16)); hsel.setScale(scale);
    hpos = sf::Vector2f(400,798);
    hselpos = hpos; pos = sf::Vector2f(302,70);
    hsel.setPosition(hselpos);

    create();

    if (!font.openFromFile("../assets/fonts/MineFont.ttf")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_FONT_FROM_FILE");
    text.setFont(font); text.setString("Press enter to revive");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color(150,150,150));
    text.setPosition(sf::Vector2f(250,650));

}

void hud::create() {
    //crear hotbar

    overS.setTextureRect({{58,4},{size}}); overS.setScale(scale);
    overS.setOrigin(sf::Vector2f(48,16)); overS.setPosition(hotbar.getPosition());
    overHb.push_back(overS); overS.setTextureRect({{58,36},{size}}); overHb.push_back(overS);

    for (size_t i=0;i<6;i++) {
        sf::Sprite s = hotbar;
        s.setPosition({hotbar.getPosition().x + 64*i,hotbar.getPosition().y});
        hotbars.push_back(s);
        // s = overS;
        // overHb.push_back(s);
    }

    for (int i=1;i<5;i++) {
        sf::Sprite s = overS;
        s.setTextureRect({{74,4},{size}});
        s.setPosition({overS.getPosition().x + 64*i,s.getPosition().y});
        overHb.push_back(s);
        s.setTextureRect({{74,36},{size}});
        overHb.push_back(s);
    }
    overS.setTextureRect({{92,4},{size}});
    overS.setPosition({overHb.back().getPosition().x + 71 ,overHb.back().getPosition().y});
    overHb.push_back(overS);
    overS.setTextureRect({{92,36},{size}}); overHb.push_back(overS);

    //crear void_health_bar
    life.setOrigin({48,16});
    life.setTextureRect({{224,260},{size}}); life.setScale({scale.x/2,scale.y/2});
    life.setPosition({pos});
    for (int i=0;i<5;i++) {
        sf::Sprite p = life;
        p.setPosition({life.getPosition().x + 38*i,life.getPosition().y});
        hp_empty.push_back(p);
    }

    createLife(playerHp);
}

void hud::createLife(int num) {
    hp_fill.clear();
    if (num < 0) num = 0;
    if (num > 20) num = 20;
    //rellena la healthbar con corazones rojos si num < 5, sino, con corazones amarillos
    life.setTextureRect({{224,224},{size}});
    sf::Sprite p = life;
    int c = 1;
    for (int i=0;i<num;i++) {
        if (i > 4) p.setTextureRect({{243,224},{size}});
        if (i%5 == 0) c++;
        p.setPosition({life.getPosition().x + 38*i,life.getPosition().y});
        hp_fill.push_back(p);
        std::cout << num << " " << i << " " << playerHp << " " << c << std::endl;
    }

}


void hud::draw(sf::RenderWindow &m_win){
    for (auto &h : hotbars) m_win.draw(h);
    for (auto &o : overHb) m_win.draw(o);
    for (auto &p : hp_empty) m_win.draw(p);
    for (auto &p : hp_fill) m_win.draw(p);
    m_win.draw(hsel);
    if (isDead) deathMessege(m_win);
    // m_win.draw(life);
}

void hud::update(){
    keyBoard();
    caseHealth();
}

void hud::updateView() {
    //reposicionamiento del hud con el resize
    for (auto &h : hotbars) {
        h.setPosition(sf::Vector2f(h.getPosition().x,newpos));
    }
    for (auto &o : overHb) {
        o.setPosition(sf::Vector2f(o.getPosition().x,newpos));
    }
    for (auto &p : hp_empty) {
        p.setPosition(sf::Vector2f(p.getPosition().x,newpos-pos.y));
    }
    for (auto &p : hp_fill) {
        p.setPosition(sf::Vector2f(p.getPosition().x,newpos-pos.y));
    }
    hselpos = sf::Vector2f(hselpos.x,newpos);
    hsel.setPosition(hselpos);
}

void hud::keyBoard(){
    if(sf::Keyboard::isKeyPressed(k_1)) hselpos = sf::Vector2f(hpos.x,newpos);
    if(sf::Keyboard::isKeyPressed(k_2)) hselpos = sf::Vector2f(hpos.x+64,newpos);
    if(sf::Keyboard::isKeyPressed(k_3)) hselpos = sf::Vector2f(hpos.x+64*2,newpos);
    if(sf::Keyboard::isKeyPressed(k_4)) hselpos = sf::Vector2f(hpos.x+64*3,newpos);
    if(sf::Keyboard::isKeyPressed(k_5)) hselpos = sf::Vector2f(hpos.x+64*4,newpos);
    if(sf::Keyboard::isKeyPressed(k_6)) hselpos = sf::Vector2f(hpos.x+64*5,newpos);
}


void hud::moveHotbar(const sf::Vector2f &winview){
    //mantener la hotbar centrada, independientemente del resize
        m_winSize = winview;
        newpos = m_winSize.y-2;
}

void hud::checkhp(int health) {
    //carga de hp
    playerHp = health;
}

void hud::caseHealth() {

    //casos dependiendo la vida del player, dibujo del hud
    if (playerHp != 0) {
        isDead = false;
        //si es par
        if (playerHp%2 == 0) {
            createLife(playerHp/2);
        }else {
            //si no es par, y es mayor a 2
            if (playerHp > 2) {
                createLife(playerHp/2);
                sf::Sprite p = life;
                if (playerHp < 10) {p.setTextureRect({{224,242},{size}});} // medio corazon rojo
                if (playerHp > 10) {p.setTextureRect({{243,242},{size}});} //medio corazon amarillo
                p.setPosition({hp_fill.back().getPosition().x + 38,hp_fill.back().getPosition().y});
                //al ser impar se le agrega medio corazon
                hp_fill.push_back(p);
            }

        }

    }
    if (playerHp == 1) {
        //medio corazon
        hp_fill.clear();
        sf::Sprite p = life; p.setTextureRect({{224,242},{size}});
        p.setPosition(life.getPosition());
        hp_fill.push_back(p);
    }
    //si esta muerto
    if (playerHp == 0 && isDead == false) {hp_fill.clear(); isDead = true;}
}

void hud::deathMessege(sf::RenderWindow &m_win) {
    //mensaje "press enter to revive"
    m_win.draw(text);
}