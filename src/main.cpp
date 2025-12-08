#include "Game.hpp"
#include "Scene.hpp"
#include "Match.hpp"
#include <iostream>
#include "menu.hpp"

int main() {
    // scene *first_scene = new match;
    Game game(new menu);
    game.run();
    return 0;
}
