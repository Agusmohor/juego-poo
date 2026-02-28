#ifndef JUEGO_POO_AUDIOMANAGER_H
#define JUEGO_POO_AUDIOMANAGER_H

#include <SFML/Audio.hpp>

class AudioManager {
    sf::SoundBuffer dash_1,dash_2,sword_1,sword_2,sword_3;
    sf::Sound dash, sword;
    void randomAudio(sf::Sound &sound,const sf::SoundBuffer &buffer1, const sf::SoundBuffer &buffer2);
    void randomAudio(sf::Sound &sound,const sf::SoundBuffer &buffer1, const sf::SoundBuffer &buffer2, const sf::SoundBuffer &buffer3);
public:
    AudioManager();
    void playDash();
    void playSword();
};

#endif