#include "Game.hpp"
#include <iostream>

Game::Game(scene* f_scene) : m_win(sf::VideoMode({800,800}), "Juego Poo"), curr_scene(f_scene), ispaused(false), next_scene(nullptr),m_pause(nullptr){
    m_win.setFramerateLimit(60);
    loadConfig(m_win);
    loadProgress();

}

void Game::run(){
    while(m_win.isOpen()){
        float delta = time.restart().asSeconds();

        // ve todos los eventos q ocurren en la ventana
        ProcessEvent();

        m_win.clear();

        if(!ispaused) curr_scene->update(delta,*this);

        if (!saveAndQuit && m_isOver){saveProgress(); m_isOver = false;}

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

void Game::ProcessEvent() {
    while(auto evt = m_win.pollEvent()){
        //evento cerrar ventana
        if(evt->is<sf::Event::Closed>()) {m_win.close();} else {
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
            m_uiview = sf::View(visibleArea); m_uiview.setCenter(m_win.getDefaultView().getCenter());
            m_win.setView(m_view);
        }
    }
}

void Game::setScene(scene *newScene){
    delete next_scene;
    next_scene = newScene;
}

Game::~Game(){
    delete curr_scene; curr_scene = nullptr;
    delete next_scene; next_scene = nullptr;
    delete m_pause; m_pause = nullptr;
}

void Game::Pause(){
    if(!ispaused){ m_pause = new PauseScene; ispaused = true; std::cout << "hola" << std::endl; }
}

void Game::delPause(){
    if (ispaused) {
        ispaused = false;
        delete m_pause; m_pause = nullptr;
        std::cout << "chau" << std::endl;
    }

}

void Game::loadConfig(sf::RenderWindow &m_win){
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

void Game::makeProfile() {
    std::ofstream file("../data/config/profile.txt");
    file << "LastProfile = null" << std::endl;
    file.close();
}

void Game::makeConfig(){
    std::ofstream cfile("../data/config/config.txt");
    cfile << "Resolution = 800x800" << std::endl;
    cfile.close();
}

void Game::makeKeybinds() {
    m_keys[0] = sf::Keyboard::Scancode::Q; m_keys[1] = sf::Keyboard::Scancode::E;
    m_keys[2] = sf::Keyboard::Scancode::R; m_keys[3] = sf::Keyboard::Scancode::F;
    kb.shield = static_cast<int>(m_keys[0]); kb.dash = static_cast<int>(m_keys[1]);
    kb.fire = static_cast<int>(m_keys[2]); kb.heal = static_cast<int>(m_keys[3]);

    std::ofstream cfile("../data/config/keybinds.dat", std::ios::binary | std::ios::trunc);
    cfile.write(reinterpret_cast<const char*>(&kb),sizeof(kb));
}

void Game::takeProfile(std::ifstream &file) {
    std::string aux;
    std::getline(file,aux);
    name = aux.substr(aux.find_last_of(' ')+1,aux.back());
    std::cout << "name:" << name << std::endl;
}

void Game::takeConfig(std::ifstream &file){
    std::string aux;
    std::getline(file,aux); 
    resolution.x = std::stoi(aux.substr(aux.find("=")+1,(aux.find("x")-aux.find("=")+1)));
    resolution.y = std::stoi(aux.substr(aux.find("x")+1));
}

const sf::Vector2u& Game::getWinSize() const {
    return m_winSize;
}

const sf::View& Game::getUIWinView() const {
    return m_uiview;
}

void Game::setStats(const stats &m_stats) {
    m_lastStats = m_stats;
}

const stats &Game::getStats() {
    return m_lastStats;
}

void Game::setKeyBinds(const std::array<sf::Keyboard::Scancode, 4> &keys, bool save) {
    m_keys = keys;
    if (save) {
        kb.shield = static_cast<int>(m_keys[0]); kb.dash = static_cast<int>(m_keys[1]);
        kb.fire = static_cast<int>(m_keys[2]); kb.heal = static_cast<int>(m_keys[3]);

        std::ofstream file("../data/config/keybinds.dat", std::ios::binary | std::ios::trunc);
        file.write(reinterpret_cast<const char*>(&kb),sizeof(kb));
    }
}

const std::array<sf::Keyboard::Scancode, 4>& Game::getKeyBinds() const {
    return m_keys;
}

void Game::setPlayerSaves(const playerSaves& psaves) {
    player_saves = psaves;
}

void Game::setZombieSaves(const zombieSave &zsave) {
    zsaves.push_back(zsave);
}

void Game::clearZsaves(){zsaves.clear();}
void Game::clearTsaves(){tsaves.clear();}

void Game::setTreeSaves(const treeSave& tsave) {
    tsaves.push_back(tsave);
}

bool Game::getSaveAndQuit() {
    return saveAndQuit;
}

void Game::setSaveAndQuit(bool saq, bool isOver) {saveAndQuit = saq; m_isOver = isOver;}

void Game::saveProgress() {
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
    file.close();
}

void Game::loadProgress() {
    std::string path = "../data/saves/" + name + ".dat";
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) return;

    file.read(reinterpret_cast<char*>(&player_saves),sizeof(player_saves));

    int zcount; zsaves.clear();
    file.read(reinterpret_cast<char*>(&zcount),sizeof(zcount));
    if (zcount < 0 || zcount > 50) return;
    zombieSave z;
    for (int i=0;i<zcount;i++) {
        file.read(reinterpret_cast<char*>(&z),sizeof(z));
        zsaves.push_back(z);
    }

    int tcount; tsaves.clear();
    file.read(reinterpret_cast<char*>(&tcount),sizeof(tcount));
    if (tcount < 0 || tcount > 600) return;
    treeSave ts;
    for (int i=0;i<tcount;i++) {
        file.read(reinterpret_cast<char*>(&ts),sizeof(ts));
        tsaves.push_back(ts);
    }
}

const playerSaves &Game::getPlayerSaves() const {
    return player_saves;
}

const std::vector<zombieSave> &Game::getZombieSaves() const {
    return zsaves;
}

const std::vector<treeSave> &Game::getTreeSaves() const {
    return tsaves;
}
