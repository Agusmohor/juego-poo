#ifndef JUEGO_POO_CONFIGMANAGER_H
#define JUEGO_POO_CONFIGMANAGER_H

#include "gameplay/Stats.hpp"
#include "fstream"
#include "iostream"
#include "Keys.hpp"

struct keybinds {
    int shield, dash, fire, heal;
};

class ConfigManager {
    void makeConfig() {
        std::ofstream cfile("../data/config/config.txt", std::ios::trunc);
        cfile << "Volume = 100" <<std::endl;
        cfile << "Music = 100"<<std::endl;
        cfile.close();
    }

    void makeProfile() {
        std::ofstream file("../data/config/profile.txt");
        file << "LastProfile = null" << std::endl;
        file.close();
    }

    void makeKeyBinds(std::array<sf::Keyboard::Scancode, 4> &keys) {
        keybinds kb;
        keys[0] = sf::Keyboard::Scancode::Q; keys[1] = sf::Keyboard::Scancode::E;
        keys[2] = sf::Keyboard::Scancode::R; keys[3] = sf::Keyboard::Scancode::F;
        kb.shield = static_cast<int>(keys[0]); kb.dash = static_cast<int>(keys[1]);
        kb.fire = static_cast<int>(keys[2]); kb.heal = static_cast<int>(keys[3]);

        std::ofstream cfile("../data/config/keybinds.dat", std::ios::binary | std::ios::trunc);
        cfile.write(reinterpret_cast<const char*>(&kb),sizeof(kb));
    }
public:
    bool loadProgess(const stats &p_stats,playerSaves& p_saves,std::vector<zombieSave>& z_saves, std::vector<treeSave>& t_saves) {
            std::string path = "../data/saves/" + p_stats.name + ".dat";
            std::ifstream file(path, std::ios::binary);

            if (!file.is_open()) return false;

            file.read(reinterpret_cast<char*>(&p_saves),sizeof(p_saves));

            int zcount; z_saves.clear();
            file.read(reinterpret_cast<char*>(&zcount),sizeof(zcount));
            if (zcount < 0 || zcount > 50) return false;
            zombieSave z;
            for (int i=0;i<zcount;i++) {
                file.read(reinterpret_cast<char*>(&z),sizeof(z));
                z_saves.push_back(z);
            }

            int tcount; t_saves.clear();
            file.read(reinterpret_cast<char*>(&tcount),sizeof(tcount));
            if (tcount < 0 || tcount > 600) return false;
            treeSave ts;
            for (int i=0;i<tcount;i++) {
                file.read(reinterpret_cast<char*>(&ts),sizeof(ts));
                t_saves.push_back(ts);
            }
        return true;
    }

    void saveProgess(const stats& stats,playerSaves& p_saves,std::vector<zombieSave>& z_saves, std::vector<treeSave>& t_saves) {
            std::string path = "../data/saves/" + stats.name + ".dat";
            std::ofstream file(path, std::ios::binary | std::ios::trunc);
            file.write(reinterpret_cast<const char*>(&p_saves),sizeof(p_saves));

            int zcount = z_saves.size();
            file.write(reinterpret_cast<const char*>(&zcount),sizeof(zcount));
            for (auto &z : z_saves) {
                file.write(reinterpret_cast<const char*>(&z),sizeof(z));
            }
            int tcount = t_saves.size();
            file.write(reinterpret_cast<const char*>(&tcount),sizeof(tcount));
            for (auto &t : t_saves) {
                file.write(reinterpret_cast<const char*>(&t),sizeof(t));
            }
            file.close(); file.clear();
    }

    void newProgress(const stats& p_stats,playerSaves& p_saves,std::vector<zombieSave>& z_saves, std::vector<treeSave>& t_saves) {
        std::string path = "../data/saves/" + p_stats.name + ".dat";
        std::ofstream file(path, std::ios::binary | std::ios::trunc);
        playerSaves s;
        file.write(reinterpret_cast<const char*>(&s),sizeof(s));
        file.close();
        t_saves.clear(); z_saves.clear(); p_saves = s;
    }

    void loadConfig(stats& p_stats,int& vol,int &music,std::array<sf::Keyboard::Scancode, 4> &keys) {
        {
            std::ifstream file("../data/config/config.txt");
            if(!file.is_open()) {
                makeConfig();
                file.open("../data/config/config.txt");
            }
            std::string aux;
            std::getline(file,aux);
            vol = std::stoi(aux.substr(aux.find("=")+1));
            std::getline(file,aux);
            music = std::stoi(aux.substr(aux.find("=")+1));
        }
        {
            std::ifstream file("../data/config/profile.txt") ;
            if (!file.is_open()) {
                makeProfile();
                file.open("../data/config/profile.txt");
            }
            std::string aux;
            std::getline(file,aux);
            p_stats.name = aux.substr(aux.find_last_of(' ')+1,aux.back());
        }
        {
            std::ifstream file("../data/config/keybinds.dat", std::ios::binary);
            if (!file.is_open()) {
                makeKeyBinds(keys);
                file.open("../data/config/keybinds.dat", std::ios::binary);
            }
            keybinds kb;
            file.read(reinterpret_cast<char*>(&kb),sizeof(kb));
            keys[0] = static_cast<sf::Keyboard::Scancode>(kb.shield);
            keys[1] = static_cast<sf::Keyboard::Scancode>(kb.dash);
            keys[2] = static_cast<sf::Keyboard::Scancode>(kb.fire);
            keys[3] = static_cast<sf::Keyboard::Scancode>(kb.heal);
        }
    }

    void saveConfig(const stats& p_stats,int vol,int& music, const std::array<sf::Keyboard::Scancode, 4> &keys) {
        std::ofstream configfile("../data/config/config.txt");
        configfile << "Volume = " << vol << std::endl;
        configfile << "Music = " << music << std::endl;
        configfile.close();

        configfile.open("../data/config/profile.txt",std::ios::trunc);
        configfile << "LastProfile = "<< p_stats.name << std::endl;

        keybinds kb;
        kb.shield = static_cast<int>(keys[0]); kb.dash = static_cast<int>(keys[1]);
        kb.fire = static_cast<int>(keys[2]); kb.heal = static_cast<int>(keys[3]);

        std::ofstream file("../data/config/keybinds.dat", std::ios::binary | std::ios::trunc);
        file.write(reinterpret_cast<const char*>(&kb),sizeof(kb));
        file.close();
    }

};

#endif



