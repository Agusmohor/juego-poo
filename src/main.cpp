#include "Game.hpp"
#include "Scene.hpp"
#include "menu.hpp"

int main() {
    Game game(new menu);
    game.run();
    return 0;
}
