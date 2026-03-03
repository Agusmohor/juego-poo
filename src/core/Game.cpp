#include "core/Game.hpp"
#include <iostream>

game::game(scene* f_scene) : m_win(sf::VideoMode({800,800}), "Juego Poo"), curr_scene(f_scene), ispaused(false), next_scene(nullptr),m_pause(nullptr){
    m_win.setFramerateLimit(60);
    loadConfig();
    m_win.setSize({801,801});
}

void game::run(){
    while(m_win.isOpen()){
        float delta = time.restart().asSeconds();

        // ve todos los eventos q ocurren en la ventana
        ProcessEvent();
        audio.setVolume(volume);
        audio.setMusicVolume(music);

        m_win.clear();
        if(ispaused && m_pause != nullptr) m_pause->update(delta,*this);
        if(!ispaused) curr_scene->update(delta,*this);

        if (saveAndQuit){saveProgress(); saveAndQuit=false;}
        if (isOver) {newProgress();}
        curr_scene->updateView(*this);


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
            saveConfig();
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

AudioManager &game::getAudio() {
    return audio;
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

const sf::Vector2u& game::getWinSize() const {
    return m_winSize;
}

const sf::View& game::getView() const {
    return m_view;
}

void game::setStats(const stats &m_stats) {
    if (m_stats.name != "null"){p_stats.name = m_stats.name;}
    p_stats.kills = m_stats.kills;
    p_stats.timeAlive = m_stats.timeAlive;
}

void game::setName(const std::string &name) {
    p_stats.name = name;
}

const stats &game::getStats() const{
    return p_stats;
}

void game::setKeyBinds(const std::array<sf::Keyboard::Scancode, 4> &keys) {
    m_keys = keys;
}

const std::array<sf::Keyboard::Scancode, 4>& game::getKeyBinds() const {
    return m_keys;
}

void game::setPlayerSaves(const playerSaves& psaves) {
    p_saves = psaves;
}

void game::setZombieSaves(const zombieSave &zsave) {
    z_saves.push_back(zsave);
}

void game::clearZsaves(){z_saves.clear();}
void game::clearTsaves(){t_saves.clear();}

void game::setTreeSaves(const treeSave& tsave) {
    t_saves.push_back(tsave);
}

bool game::getSaveAndQuit() {
    return saveAndQuit;
}

bool game::loadProgress() {
    return config.loadProgess(p_stats,p_saves,z_saves,t_saves);
}

void game::saveProgress() {
    config.saveProgess(p_stats,p_saves,z_saves,t_saves);
}

void game::newProgress() {
    config.newProgress(p_stats,p_saves,z_saves,t_saves);
}

void game::saveConfig() {
    config.saveConfig(p_stats,volume,music,m_keys);
}

void game::loadConfig() {
    config.loadConfig(p_stats,volume,music,m_keys);
}

void game::setSaveAndQuit(bool saq) {saveAndQuit = saq;}

void game::setIsOver(bool isover) {isOver = isover;}

bool game::getIsOver() {return isOver;}



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
    return p_saves;
}

const std::vector<zombieSave> &game::getZombieSaves() const {
    return z_saves;
}

const std::vector<treeSave> &game::getTreeSaves() const {
    return t_saves;
}

void game::setVolume(int vol) {
    volume = vol;
}

int game::getVolume() const {
    return volume;
}

void game::setVolMusic(int vol) {
    music = vol;
}

int game::getVolMusic() const {
    return music;
}
