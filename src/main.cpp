#include "core/Game.hpp"
#include "core/Scene.hpp"
#include "scenes/menu.hpp"
#include <ctime>
#include <cstdlib>


int main() {
    std::srand(std::time(nullptr));

    game game(new menu);
    game.run();
    return 0;
}
