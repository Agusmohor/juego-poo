#include "Game.hpp"
#include "Scene.hpp"
#include "Match.hpp"
#include <iostream>

int main() {
    // scene *first_scene = new match;
    Game game(new match);
    game.run();
    return 0;
}
