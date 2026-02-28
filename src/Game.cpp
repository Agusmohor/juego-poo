#include "Game.hpp"
#include <iostream>

game::game(scene* f_scene) : m_win(sf::VideoMode({800,800}), "Juego Poo"), curr_scene(f_scene), ispaused(false), next_scene(nullptr),m_pause(nullptr){
    m_win.setFramerateLimit(60);
    loadConfig(m_win);

}

void game::run(){
    while(m_win.isOpen()){
        float delta = time.restart().asSeconds();

        // ve todos los eventos q ocurren en la ventana
        ProcessEvent();

        m_win.clear();
        if(!ispaused) curr_scene->update(delta,*this);

        if (!saveAndQuit && isOver){saveProgress();}

        curr_scene->updateView(*this);
        if(ispaused && m_pause != nullptr) m_pause->update(delta,*this);

        curr_scene->draw(m_win);
        if(ispaused && m_pause != nullptr) m_pause->draw(m_win);

        m_win.display();
        if(next_scene != nullptr){
            delete curr_scene;
            curr_scene = next_scene;
            next_scene = nullptr;
        }
    }

}

void game::ProcessEvent() {
    while(auto evt = m_win.pollEvent()){
        //evento cerrar ventana
        if(evt->is<sf::Event::Closed>() || isExit) {
            saveProgress();
            m_win.close();
        } else {
            sf::Event& event = *evt;
            if (ispaused && m_pause) {m_pause->ProcessEvent(*this,event);}
            else{curr_scene->ProcessEvent(*this,event);}

        }

        //evento resize ventana
        if(const auto* resized = evt->getIf<sf::Event::Resized>()){

            m_winSize = sf::Vector2u(resized->size);
            sf::FloatRect visibleArea({0.f,0.f},sf::Vector2f(m_winSize));

            //centra la view cuando se hace un resize de la window
            m_view = sf::View(visibleArea); m_view.setCenter(m_win.getDefaultView().getCenter());
            m_win.setView(m_view);
        }
    }
}

void game::setScene(scene *newScene){
    delete next_scene;
    next_scene = newScene;
}

game::~game(){
    delete curr_scene; curr_scene = nullptr;
    delete next_scene; next_scene = nullptr;
    delete m_pause; m_pause = nullptr;
}

void game::Pause(){
    if(!ispaused){ m_pause = new PauseScene; ispaused = true;}
}

void game::delPause(){
    if (ispaused) {
        ispaused = false;
        delete m_pause; m_pause = nullptr;
    }

}

const sf::RenderWindow &game::getWindow() const {
    return m_win;
}

void game::loadConfig(sf::RenderWindow &m_win){
    {
        std::ifstream file("../data/config/config.txt");
        if(!file.is_open()) {
            makeConfig();
            file.open("../data/config/config.txt");
        }
        takeConfig(file);
        m_win.setSize(resolution);
    }
    {
        std::ifstream file("../data/config/profile.txt") ;
        if (!file.is_open()) {
            makeProfile();
            file.open("../data/config/profile.txt");
        }
        takeProfile(file);
    }
    {
        std::ifstream file("../data/config/keybinds.dat", std::ios::binary);
        if (!file.is_open()) {
            makeKeybinds();
            file.open("../data/config/keybinds.dat", std::ios::binary);
        }
        file.read(reinterpret_cast<char*>(&kb),sizeof(kb));
        m_keys[0] = static_cast<sf::Keyboard::Scancode>(kb.shield);
        m_keys[1] = static_cast<sf::Keyboard::Scancode>(kb.dash);
        m_keys[2] = static_cast<sf::Keyboard::Scancode>(kb.fire);
        m_keys[3] = static_cast<sf::Keyboard::Scancode>(kb.heal);
    }

}

void game::makeProfile() {
    std::ofstream file("../data/config/profile.txt");
    file << "LastProfile = null" << std::endl;
    file.close();
}

void game::makeConfig(){
    std::ofstream cfile("../data/config/config.txt");
    cfile << "Resolution = 800x800" << std::endl;
    cfile.close();
}

void game::makeKeybinds() {
    m_keys[0] = sf::Keyboard::Scancode::Q; m_keys[1] = sf::Keyboard::Scancode::E;
    m_keys[2] = sf::Keyboard::Scancode::R; m_keys[3] = sf::Keyboard::Scancode::F;
    kb.shield = static_cast<int>(m_keys[0]); kb.dash = static_cast<int>(m_keys[1]);
    kb.fire = static_cast<int>(m_keys[2]); kb.heal = static_cast<int>(m_keys[3]);

    std::ofstream cfile("../data/config/keybinds.dat", std::ios::binary | std::ios::trunc);
    cfile.write(reinterpret_cast<const char*>(&kb),sizeof(kb));
}

void game::takeProfile(std::ifstream &file) {
    std::string aux;
    std::getline(file,aux);
    name = aux.substr(aux.find_last_of(' ')+1,aux.back());
    m_lastStats.name = name;
}

void game::takeConfig(std::ifstream &file){
    std::string aux;
    std::getline(file,aux); 
    resolution.x = std::stoi(aux.substr(aux.find("=")+1,(aux.find("x")-aux.find("=")+1)));
    resolution.y = std::stoi(aux.substr(aux.find("x")+1));
}

const sf::Vector2u& game::getWinSize() const {
    return m_winSize;
}

const sf::View& game::getView() const {
    return m_view;
}

void game::setStats(const stats &m_stats) {
    if (m_stats.name != "null"){m_lastStats.name = m_stats.name;}
    m_lastStats.kills = m_stats.kills;
    m_lastStats.timeAlive = m_stats.timeAlive;
}

const stats &game::getStats() {
    return m_lastStats;
}

void game::setKeyBinds(const std::array<sf::Keyboard::Scancode, 4> &keys, bool save) {
    m_keys = keys;
    if (save) {
        kb.shield = static_cast<int>(m_keys[0]); kb.dash = static_cast<int>(m_keys[1]);
        kb.fire = static_cast<int>(m_keys[2]); kb.heal = static_cast<int>(m_keys[3]);

        std::ofstream file("../data/config/keybinds.dat", std::ios::binary | std::ios::trunc);
        file.write(reinterpret_cast<const char*>(&kb),sizeof(kb));
    }
}

const std::array<sf::Keyboard::Scancode, 4>& game::getKeyBinds() const {
    return m_keys;
}

void game::setPlayerSaves(const playerSaves& psaves) {
    player_saves = psaves;
}

void game::setZombieSaves(const zombieSave &zsave) {
    zsaves.push_back(zsave);
}

void game::clearZsaves(){zsaves.clear();}
void game::clearTsaves(){tsaves.clear();}

void game::setTreeSaves(const treeSave& tsave) {
    tsaves.push_back(tsave);
}

bool game::getSaveAndQuit() {
    return saveAndQuit;
}

void game::setSaveAndQuit(bool saq) {saveAndQuit = saq;}

void game::setIsOver(bool isover) {isOver = isover;}

bool game::getIsOver() {return isOver;}

void game::saveProgress() {
    std::string path = "../data/saves/" + name + ".dat";
    std::ofstream file(path, std::ios::binary | std::ios::trunc);
    file.write(reinterpret_cast<const char*>(&player_saves),sizeof(player_saves));

    int zcount = zsaves.size();
    file.write(reinterpret_cast<const char*>(&zcount),sizeof(zcount));
    for (auto &z : zsaves) {
        file.write(reinterpret_cast<const char*>(&z),sizeof(z));
    }
    int tcount = tsaves.size();
    file.write(reinterpret_cast<const char*>(&tcount),sizeof(tcount));
    for (auto &t : tsaves) {
        file.write(reinterpret_cast<const char*>(&t),sizeof(t));
    }
    file.close(); file.clear();
    file.open("../data/config/profile.txt",std::ios::trunc);
    file << "LastProfile = "<< m_lastStats.name << std::endl;
    std::cout<<"guarde "<< m_lastStats.name <<std::endl;
}

bool game::loadProgress() {
    std::string path = "../data/saves/" + name + ".dat";
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) return false;

    file.read(reinterpret_cast<char*>(&player_saves),sizeof(player_saves));

    int zcount; zsaves.clear();
    file.read(reinterpret_cast<char*>(&zcount),sizeof(zcount));
    if (zcount < 0 || zcount > 50) return true;
    zombieSave z;
    for (int i=0;i<zcount;i++) {
        file.read(reinterpret_cast<char*>(&z),sizeof(z));
        zsaves.push_back(z);
    }

    int tcount; tsaves.clear();
    file.read(reinterpret_cast<char*>(&tcount),sizeof(tcount));
    if (tcount < 0 || tcount > 600) return true;
    treeSave ts;
    for (int i=0;i<tcount;i++) {
        file.read(reinterpret_cast<char*>(&ts),sizeof(ts));
        tsaves.push_back(ts);
    }
    return true;
}

void game::newProgress() {
    std::string path = "../data/saves/" + name + ".dat";
    std::ofstream file(path, std::ios::binary | std::ios::trunc);
    playerSaves s;
    file.write(reinterpret_cast<const char*>(&s),sizeof(s));
    file.close();
    tsaves.clear(); zsaves.clear(); player_saves = s;
}

void game::setNewMatch(bool b) {
    newMatch = b;
}

void game::exit() {
    isExit = true;
}

bool game::isNewMatch() {
    return newMatch;
}

const playerSaves &game::getPlayerSaves() const {
    return player_saves;
}

const std::vector<zombieSave> &game::getZombieSaves() const {
    return zsaves;
}

const std::vector<treeSave> &game::getTreeSaves() const {
    return tsaves;
}
