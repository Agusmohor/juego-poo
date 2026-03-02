#include "core/AudioManager.hpp"

#include <iostream>

AudioManager::AudioManager() : dash(dash_1), sword(sword_1), fire(fire_1),heal(heal_1),shieldStart(shield_1),shieldFinish(shield_2),
e_damaged(damaged_1), e_dead(dead_1), p_damaged(pdamaged_1), p_dead(pdamaged_1), p_walk(pwalk_1),p_run(pwalk_1),s_dam(sdam_1),e_walk(pwalk_1),
danger(danger_1),music(music_1),music_Over(musicOver_1)
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
    if (!sdam_1.loadFromFile("../assets/sounds/sdamage1.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!sdam_2.loadFromFile("../assets/sounds/sdamage2.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!sdam_3.loadFromFile("../assets/sounds/sdamage3.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!danger_1.loadFromFile("../assets/sounds/danger.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!music_1.loadFromFile("../assets/sounds/music1.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!music_2.loadFromFile("../assets/sounds/music2.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");
    if (!musicOver_1.loadFromFile("../assets/sounds/music_over.ogg")) throw std::runtime_error("ERROR:COULD_NOT_LOAD_SOUND_FROM_FILE");

    shieldStart.setBuffer(shield_1); shieldFinish.setBuffer(shield_2);
    p_walk.setLooping(true); p_walk.setPitch(1.3); p_run.setLooping(true); p_run.setPitch(1.5);
    danger.setLooping(true); music.setLooping(true); music_Over.setLooping(true);

}

void AudioManager::setVolume(float volume) {
    dash.setVolume(volume);
    sword.setVolume(volume);
    fire.setVolume(volume);
    heal.setVolume(volume);
    shieldStart.setVolume(volume);
    shieldFinish.setVolume(volume);
    e_damaged.setVolume(volume);
    e_dead.setVolume(volume);
    p_damaged.setVolume(volume);
    p_dead.setVolume(volume);
    p_walk.setVolume(volume);
    p_run.setVolume(volume);
    s_dam.setVolume(volume);
    e_walk.setVolume(volume);
    danger.setVolume(volume);
}

void AudioManager::setMusicVolume(float volume) {
    music.setVolume(volume);
    music_Over.setVolume(volume);
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

void AudioManager::playShieldDamaged() {
    randomAudio(s_dam,sdam_1,sdam_2,sdam_3);
    s_dam.play();
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
    randomAudio(p_dead,pdead_1,pdead_2,pdead_3);
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

void AudioManager::playDanger() {
    danger.play();
}

void AudioManager::stopDanger() {
    danger.stop();
}

void AudioManager::playMusic() {
    randomAudio(music,music_1,music_2);
    music.play();
}

void AudioManager::stopMusic() {
    music.stop();
}

void AudioManager::playMusicOver() {
    music_Over.play();
}

void AudioManager::stopMusicOver() {
    music_Over.stop();
}
