#ifndef JUEGO_POO_CONFIGMANAGER_H
#define JUEGO_POO_CONFIGMANAGER_H

#include "gameplay/Stats.hpp"
#include <SFML/Window.hpp>
#include "fstream"
#include "Keys.hpp"

struct keybinds {
    int shield, dash, fire, heal;
};

class ConfigManager {
    void makeConfig();

    void makeProfile();

    void makeKeyBinds(std::array<sf::Keyboard::Scancode, 4> &keys);
public:
    bool loadProgess(const stats &p_stats,playerSaves& p_saves,std::vector<zombieSave>& z_saves, std::vector<treeSave>& t_saves);

    void saveProgess(const stats& stats,playerSaves& p_saves,std::vector<zombieSave>& z_saves, std::vector<treeSave>& t_saves);

    void newProgress(const stats& p_stats,playerSaves& p_saves,std::vector<zombieSave>& z_saves, std::vector<treeSave>& t_saves);

    void loadConfig(stats& p_stats,int& vol,int &music,std::array<sf::Keyboard::Scancode, 4> &keys);

    void saveConfig(const stats& p_stats,int vol,int& music, const std::array<sf::Keyboard::Scancode, 4> &keys);

};

#endif



