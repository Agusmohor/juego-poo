#include "core/AudioManager.hpp"

#include <iostream>

AudioManager::AudioManager() : dash(dash_1), sword(dash_1), fire(dash_1){
    if (!dash_1.loadFromFile("../assets/sounds/dash1.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!dash_2.loadFromFile("../assets/sounds/dash2.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!sword_1.loadFromFile("../assets/sounds/sword1.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!sword_2.loadFromFile("../assets/sounds/sword2.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!sword_3.loadFromFile("../assets/sounds/sword3.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!fire_1.loadFromFile("../assets/sounds/fire1.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!fire_2.loadFromFile("../assets/sounds/fire2.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
}

void AudioManager::randomAudio(sf::Sound &sound, const sf::SoundBuffer &buffer1, const sf::SoundBuffer &buffer2) {
    int rng = rand()%2;
    switch (rng) {
        case 0: sound.setBuffer(buffer1); break;
        case 1: sound.setBuffer(buffer2); break;
    }
}

void AudioManager::randomAudio(sf::Sound &sound, const sf::SoundBuffer &buffer1, const sf::SoundBuffer &buffer2, const sf::SoundBuffer &buffer3) {
    int rng = rand()%2;
    switch (rng) {
        case 0: sound.setBuffer(buffer1); break;
        case 1: sound.setBuffer(buffer2); break;
        case 2: sound.setBuffer(buffer3); break;
    }
}

void AudioManager::playDash() {
    randomAudio(dash,dash_1,dash_2);
    dash.play();
}

void AudioManager::playSword() {
    randomAudio(sword,sword_1,sword_2,sword_3);
    sword.play();
}

void AudioManager::playFireBall() {
    randomAudio(fire,fire_1,fire_2);
    fire.play();
}
