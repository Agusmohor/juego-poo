#ifndef JUEGO_POO_STATS_H
#define JUEGO_POO_STATS_H

#include <string>

struct playerSaves {
    float x = 1120;
    float y = 1184;
    float health = 10;
    float stam = 180;
    float time = 0;
    int kills = 0;

};

bool operator==(const playerSaves &a, const playerSaves &b);

struct stats {
    std::string name = "null";
    float timeAlive = 0.f;
    int kills = 0;
};

struct zombieSave {
    float x = 0;
    float y = 0;
};



struct treeSave {
    float x = 0;
    float y = 0;
};

#endif