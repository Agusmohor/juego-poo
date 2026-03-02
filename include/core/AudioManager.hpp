#ifndef JUEGO_POO_AUDIOMANAGER_H
#define JUEGO_POO_AUDIOMANAGER_H

#include <SFML/Audio.hpp>

class AudioManager {
    sf::SoundBuffer dash_1,dash_2,sword_1,sword_2,sword_3,fire_1,fire_2,heal_1,heal_2,shield_1,shield_2,damaged_1,damaged_2,damaged_3,dead_1,dead_2,dead_3;
    sf::SoundBuffer pdamaged_1, pdamaged_2,pdead_1,pdead_2,pdead_3,pwalk_1,pwalk_2,pwalk_3,sdam_1,sdam_2,sdam_3,danger_1,music_1,music_2,music_3,musicOver_1;
    sf::Sound dash, sword,fire,heal,shieldStart,shieldFinish,e_damaged,e_dead,p_damaged,p_dead,p_walk,p_run,s_dam,e_walk,danger,music,music_Over;
    void randomAudio(sf::Sound &sound,const sf::SoundBuffer &buffer1, const sf::SoundBuffer &buffer2);
    void randomAudio(sf::Sound &sound,const sf::SoundBuffer &buffer1, const sf::SoundBuffer &buffer2, const sf::SoundBuffer &buffer3);
public:
    AudioManager();
    void setVolume(float volume);
    void setMusicVolume(float volume);

    void playDash();
    void playSword();
    void playFireBall();
    void playHeal();
    void playStartShield();
    void playFinishShield();
    void playShieldDamaged();

    void playEntityDamaged();
    void playEntityDeath();

    void playPlayerDamaged();
    void playPlayerDeath();
    void playPlayerWalking();
    void stopPlayerWalking();
    void playPlayerRunning();
    void stopPlayerRunning();

    void playDanger();
    void stopDanger();

    void playMusic();
    void stopMusic();
    void playMusicOver();
    void stopMusicOver();
};

#endif