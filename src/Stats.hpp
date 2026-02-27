#ifndef JUEGO_POO_STATS_H
#define JUEGO_POO_STATS_H

struct playerSaves {
    float x = 0;
    float y = 0;
    float health = 0;
    float stam = 0;
    float time = 0;
    int kills = 0;

};

bool operator==(const playerSaves &a, const playerSaves &b);


struct zombieSave {
    float x = 0;
    float y = 0;
};



struct treeSave {
    float x = 0;
    float y = 0;
};

#endif