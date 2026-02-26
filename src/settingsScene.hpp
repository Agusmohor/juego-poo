#ifndef JUEGO_POO_SETTINGSSCENE_H
#define JUEGO_POO_SETTINGSSCENE_H
#include "Scene.hpp"
#include "Keys.hpp"

enum struct type {
    resume,
    setting,
    exit,
    Ab1, Ab2, Ab3, Ab4
};



class settingsScene : public scene{
    sf::RectangleShape background, Ab1,Ab2,Ab3,Ab4, exit;
    sf::Texture boton,botonselec;
    sf::Font font; sf::Text ab1Text,ab2Text,ab3Text,ab4Text, exitText, k1,k2,k3,k4;
    std::array<sf::Keyboard::Scancode,4> m_keys;
    bool waitingForKey = false;
    bool lbuttonpressed = false;
    bool isexit = false;
    bool isRecentlyOpen;
    action curraction;



    void button_overlay(const sf::RenderWindow &win, sf::RectangleShape &button, type t);

    std::string keyToString(sf::Keyboard::Scancode key);



public:
    settingsScene();
    void update(float delta,Game &m_gam) override;
    void ProcessEvent(Game &game, sf::Event &event) override;
    void updateView(Game &m_gam) override;
    void draw(sf::RenderWindow &m_win) override;
    void setKey(sf::Keyboard::Scancode key);
    const std::array<sf::Keyboard::Scancode,4>& getKeyBinds() const;
    bool isWaitingForKey() const;
    bool getExit() const;
    void setExit(bool exit);
    bool getIsRecentlyOpen() const;
    void setIsRecentlyOpen(bool active);

};


#endif