#include "Game.hpp"
#include "Scene.hpp"
#include "menu.hpp"
#include <ctime>
#include <cstdlib>


int main() {
    std::srand(std::time(nullptr));

    Game game(new menu);
    game.run();
    return 0;
}
