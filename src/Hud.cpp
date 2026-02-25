#include "Hud.hpp"
#include <iostream>
#include "Player.hpp"

hud::hud() : gui("../assets/textures/entity/player/gui/gui.png"), life(gui), m_shield(gui),m_dash(gui),m_fire(gui),m_heal(gui), overlay(gui),font("../assets/fonts/MineFont.ttf"), text(font,""), playerHp(5){

    if(!gui.loadFromFile("../assets/textures/entity/player/gui/gui.png")) throw std::runtime_error("ERROR:COULD_NOT_OPEN_GUI_TEXTURE_FROM_FILE");

    size = sf::Vector2i(16,16);
    scale = sf::Vector2f(4,4);
    pos = sf::Vector2f(302,20);
    abilPos = sf::Vector2f(100,35);
    overlayPos = sf::Vector2f(88,41);

    create();

    if (!font.openFromFile("../assets/fonts/MineFont.ttf")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_FONT_FROM_FILE");
    text.setFont(font); text.setString("Press enter to exit");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color(150,150,150));
    text.setPosition(sf::Vector2f(250,650));

    stamColor = life.getColor();
}

void hud::create() {
    //crear shield
    m_shield.setTextureRect({{149,188},{size}}); m_shield.setOrigin({8,8});
    m_shield.setPosition({abilPos}); m_shield.setScale({3,3});
    //crear dash
    m_dash = m_shield; m_dash.setTextureRect({{185,188},{size}}); m_dash.setPosition({m_shield.getPosition().x + 65,1});
    m_dash.setScale(scale);
    //crear fire
    m_fire = m_shield; m_fire.setTextureRect({{218,188},{size}}); m_fire.setPosition({abilPos.x + 520,1});
    m_fire.setScale(scale);
    //crear heal
    m_heal = m_shield; m_heal.setTextureRect({{222,170},{size}}); m_heal.setPosition({m_fire.getPosition().x + 65,1});
    //crear void_health_bar
    life.setOrigin({48,16});
    life.setTextureRect({{224,260},{size}}); life.setScale({scale.x/2,scale.y/2});
    life.setPosition({pos});
    for (int i=0;i<5;i++) {
        sf::Sprite p = life;
        p.setPosition({life.getPosition().x+38*i,life.getPosition().y});
        hp_empty.push_back(p);
    }
    spos = sf::Vector2f((pos.x+38*5 ) + 10,pos.y);
    for (int i=0;i<6;i++) {
        sf::Sprite p=life;
        p.setTextureRect({{224,278},{size}});
        p.setPosition({spos.x+30*i,pos.y});
        stamina_empty.push_back(p);
    }

    //crear overlay
    for (int i=0;i<11;i++) {
        sf::Sprite s = m_shield;
        s.setTextureRect({{148,160},{20,20}});
        s.setPosition({overlayPos.x + 60*i,overlayPos.y});
        m_overlay.push_back(s);
    }

    createLife(playerHp);
    createStamina(6);
}

void hud::createLife(int num) {
    hp_fill.clear();
    if (num < 0) num = 0;
    if (num > 10) num = 10;
    //rellena la healthbar con corazones rojos si num < 5, sino, con corazones amarillos
    life.setTextureRect({{224,224},{size}});
    sf::Sprite p = life;
    int c = 0;
    for (int i=0;i<num;i++) {
        p.setPosition({life.getPosition().x + 38*i,life.getPosition().y});
        if (i > 4) {
            p.setTextureRect({{243,224},{size}});
            p.setPosition({life.getPosition().x+38*c,life.getPosition().y+36});
            c++;
        }
        hp_fill.push_back(p);
        // std::cout << num << " " << i << " " << playerHp << " " << c << std::endl;
    }



}

void hud::createStamina(int num) {
    if (num < 0) num = 0;
    if (num > 10) num = 10;
    stamina_bar.clear();
    sf::Sprite p = life;
    if (!isStaminaEmpty) p.setTextureRect({{243,260},{size}});
    if (isStaminaEmpty) p.setTextureRect({{224,206},{size}});
    for (int i=0;i<num;i++) {
        p.setPosition({spos.x+30*i,life.getPosition().y});
        stamina_bar.push_back(p);
    }
}

void hud::draw(sf::RenderWindow &m_win){
    for (auto &p : m_overlay) m_win.draw(p);
    for (auto &p : stamina_empty) m_win.draw(p);
    for (auto &p : stamina_bar) m_win.draw(p);
    for (auto &p : hp_empty) m_win.draw(p);
    for (auto &p : hp_fill) m_win.draw(p);
    if (isDead) deathMessege(m_win);
    m_win.draw(m_shield);
    m_win.draw(m_dash);
    m_win.draw(m_fire);
    m_win.draw(m_heal);
    // m_win.draw(life);
}

void hud::update(){
    caseHealth(); caseStamina();
}

void hud::updateView() {
    //reposicionamiento del hud con el resize
    for (auto &p : m_overlay){p.setPosition({p.getPosition().x,newpos-overlayPos.y});}
    for (auto &p : hp_empty) {
        p.setPosition(sf::Vector2f(p.getPosition().x,newpos-pos.y));
    }
    for (auto &p : hp_fill) {
        p.setPosition(sf::Vector2f(p.getPosition().x,newpos-pos.y));
    }
    for (auto &p : stamina_empty) {
        p.setPosition(sf::Vector2f(p.getPosition().x,newpos-pos.y));
    }
    for (auto &p : stamina_bar) {
        p.setPosition(sf::Vector2f(p.getPosition().x,newpos-pos.y));
    }
    m_shield.setPosition({m_shield.getPosition().x,newpos-abilPos.y});
    m_dash.setPosition({m_dash.getPosition().x,newpos-abilPos.y});
    m_fire.setPosition({m_fire.getPosition().x,newpos-abilPos.y});
    m_heal.setPosition({m_heal.getPosition().x,newpos-abilPos.y});
}

void hud::moveGui(const sf::Vector2f &winview){
    //mantener la gui centrada, independientemente del resize
        m_winSize = winview;
        newpos = m_winSize.y - 2;
}

void hud::checkPlayer(int health,int stamina, bool isStaminaEmpty) {
    //carga de hp
    playerHp = health;
    playerStam = stamina;
    this->isStaminaEmpty = isStaminaEmpty;
}

void hud::caseHealth() {
    //si esta muerto
    if (playerHp <= 0 && isDead == false) {hp_fill.clear(); isDead = true; return;}

    //casos dependiendo la vida del player, dibujo del hud
    if (playerHp > 0) {
        isDead = false;
        //si es par
        if (playerHp%2 == 0) {
            createLife(playerHp/2);
        }else {
            //si no es par, y es mayor a 2
            if (playerHp > 2) {
                createLife(playerHp/2);
                sf::Sprite p = life;
                int c=0;
                if (playerHp < 10) {p.setTextureRect({{224,242},{size}}); c = 0;} // medio corazon rojo
                if (playerHp > 10) {p.setTextureRect({{243,242},{size}}); c = 1;} //medio corazon amarillo
                p.setPosition({hp_fill.back().getPosition().x+38,p.getPosition().y+36*c});
                //al ser impar se le agrega medio corazon
                if (playerHp == 11) p.setPosition({life.getPosition().x,p.getPosition().y});
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
}

void hud::caseStamina() {
    if (playerStam <= 0) {stamina_bar.clear(); return;}

    int bars = playerStam / 30;
    if (bars > 6) bars = 6;

    int full = playerStam / 30;
    int rem = playerStam % 30;

    createStamina(bars);
        if (rem >= 15 && full < 6) {
            sf::Sprite p = life;
            if (!isStaminaEmpty) p.setTextureRect({{243,278},{size}});
            if (isStaminaEmpty) p.setTextureRect({{243,206},{size}});
            p.setPosition({spos.x + 30 * full,life.getPosition().y});
            stamina_bar.push_back(p);
        }


    if (playerStam >= 15 && playerStam <= 30) {
        stamina_bar.clear();
        sf::Sprite p = life;
        if (!isStaminaEmpty) p.setTextureRect({{243,278},{size}});
        if (isStaminaEmpty) p.setTextureRect({{243,206},{size}});
        p.setPosition({ spos.x,life.getPosition().y});
        stamina_bar.push_back(p);
    }


}

void hud::deathMessege(sf::RenderWindow &m_win) {
    //mensaje "press enter to revive"
    m_win.draw(text);
}

void hud::abilities(bool isShieldReady, bool isDashReady, bool isFireReady, bool isHealReady) {
    if (isShieldReady) {m_shield.setTextureRect({{149,188},{size}});} else {m_shield.setTextureRect({{167,188},{size}});}
    if (isDashReady) {m_dash.setTextureRect({{184,188},{size}});} else {m_dash.setTextureRect({{201,188},{size}});}
    if (isFireReady) {m_fire.setTextureRect({{218,188},{size}});} else {m_fire.setTextureRect({{234,188},{size}});}
    if (isHealReady) {m_heal.setTextureRect({{222,170},{size}});} else {m_heal.setTextureRect({{240,170},{size}});}
}


