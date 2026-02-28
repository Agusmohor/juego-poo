#include "gameplay/Stats.hpp"

bool operator==(const playerSaves &a, const playerSaves &b) {
    return a.health == b.health && a.stam == b.stam && a.time == b.time && a.kills == b.kills && a.x == b.x && a.y == b.y;
}