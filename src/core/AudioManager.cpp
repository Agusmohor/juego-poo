#include "core/AudioManager.hpp"

#include <iostream>

AudioManager::AudioManager() : dash(dash_1){
    if (!dash_1.loadFromFile("../assets/sounds/dash1.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!dash_2.loadFromFile("../assets/sounds/dash2.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
}

void AudioManager::randomAudio(sf::Sound &sound, const sf::SoundBuffer &buffer1, const sf::SoundBuffer &buffer2) {
    int rng = rand()%2;
    switch (rng) {
        case 0: sound.setBuffer(buffer1); break;
        case 1: sound.setBuffer(buffer2); break;
    }
}

void AudioManager::playDash() {
    randomAudio(dash,dash_1,dash_2);
    dash.play();
}
