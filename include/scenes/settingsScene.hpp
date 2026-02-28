#ifndef JUEGO_POO_SETTINGSSCENE_H
#define JUEGO_POO_SETTINGSSCENE_H
#include "core/Scene.hpp"
#include "core/Keys.hpp"


class settingsScene : public scene{
    sf::RectangleShape background, Ab1,Ab2,Ab3,Ab4, exit, save;
    sf::Texture boton,botonselec;
    sf::Font font;
    sf::Text ab1Text,ab2Text,ab3Text,ab4Text, exitText,saveText, k1,k2,k3,k4, waitkey;
    std::array<sf::Keyboard::Scancode,4> m_keys;
    bool waitingForKey = false;
    bool isexit = false; bool isSave = false;
    bool isRecentlyOpen = true;
    action curraction;




    std::string keyToString(sf::Keyboard::Scancode key);
    void buttonPressed( type t) override;


public:
    settingsScene();
    void update(float delta,game &m_gam) override;
    void ProcessEvent(game &game, sf::Event &event) override;
    void updateView(game &m_gam) override;
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