#include "core/AudioManager.hpp"

#include <iostream>

AudioManager::AudioManager() : dash(dash_1), sword(sword_1), fire(fire_1),heal(heal_1),shieldStart(shield_1),shieldFinish(shield_2),
e_damaged(damaged_1), e_dead(dead_1), p_damaged(pdamaged_1), p_dead(pdamaged_1), p_walk(pwalk_1),p_run(pwalk_1)
{
    if (!dash_1.loadFromFile("../assets/sounds/dash1.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!dash_2.loadFromFile("../assets/sounds/dash2.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!sword_1.loadFromFile("../assets/sounds/sword1.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!sword_2.loadFromFile("../assets/sounds/sword2.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!sword_3.loadFromFile("../assets/sounds/sword3.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!fire_1.loadFromFile("../assets/sounds/fire1.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!fire_2.loadFromFile("../assets/sounds/fire2.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!heal_1.loadFromFile("../assets/sounds/heal1.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!heal_2.loadFromFile("../assets/sounds/heal2.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!shield_1.loadFromFile("../assets/sounds/startShield.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!shield_2.loadFromFile("../assets/sounds/finishShield.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    shieldStart.setBuffer(shield_1); shieldFinish.setBuffer(shield_2);
    if (!damaged_1.loadFromFile("../assets/sounds/damaged1.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!damaged_2.loadFromFile("../assets/sounds/damaged2.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!damaged_3.loadFromFile("../assets/sounds/damaged3.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!dead_1.loadFromFile("../assets/sounds/dead1.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!dead_2.loadFromFile("../assets/sounds/dead2.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!dead_3.loadFromFile("../assets/sounds/dead3.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!pdamaged_1.loadFromFile("../assets/sounds/pdamaged1.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!pdamaged_2.loadFromFile("../assets/sounds/pdamaged2.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!pdead_1.loadFromFile("../assets/sounds/death1.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!pdead_2.loadFromFile("../assets/sounds/death2.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!pdead_3.loadFromFile("../assets/sounds/death3.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!pwalk_1.loadFromFile("../assets/sounds/walking1.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!pwalk_2.loadFromFile("../assets/sounds/walking2.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!pwalk_3.loadFromFile("../assets/sounds/walking3.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    p_walk.setLooping(true); p_walk.setPitch(1.3); p_run.setLooping(true); p_run.setPitch(1.5);

}

void AudioManager::randomAudio(sf::Sound &sound, const sf::SoundBuffer &buffer1, const sf::SoundBuffer &buffer2) {
    int rng = rand()%2;
    switch (rng) {
        case 0: sound.setBuffer(buffer1); break;
        case 1: sound.setBuffer(buffer2); break;
    }
}

void AudioManager::randomAudio(sf::Sound &sound, const sf::SoundBuffer &buffer1, const sf::SoundBuffer &buffer2, const sf::SoundBuffer &buffer3) {
    int rng = rand()%3;
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

void AudioManager::playHeal() {
    randomAudio(heal,heal_1,heal_2);
    heal.play();
}

void AudioManager::playStartShield() {
    shieldStart.play();
}

void AudioManager::playFinishShield() {
    shieldFinish.play();
}

void AudioManager::playEntityDamaged() {
    randomAudio(e_damaged,damaged_1,damaged_2,damaged_3);
    e_damaged.play();
}

void AudioManager::playEntityDeath() {
    randomAudio(e_dead,dead_1,dead_2,dead_3);
    e_dead.play();
}

void AudioManager::playPlayerDamaged() {
    randomAudio(p_damaged,pdamaged_1,pdamaged_2);
    p_damaged.play();
}

void AudioManager::playPlayerDeath() {
    randomAudio(p_dead,dead_1,dead_2,dead_3);
    p_dead.play();
}

void AudioManager::playPlayerWalking() {
    randomAudio(p_walk,pwalk_1,pwalk_2,pwalk_3);
    p_walk.play();
}

void AudioManager::stopPlayerWalking() {
    p_walk.stop();
}

void AudioManager::playPlayerRunning() {
    randomAudio(p_walk,pwalk_1,pwalk_2,pwalk_3);
    p_run.play();
}

void AudioManager::stopPlayerRunning() {
    p_run.stop();
}
