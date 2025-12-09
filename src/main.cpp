#include "Game.hpp"
#include "Scene.hpp"
#include "Match.hpp"
#include <iostream>

int main() {
    // scene *first_scene = new match;
    match m;
    Game game(m);
    game.run();
    return 0;
}
