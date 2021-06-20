
#include "Game.hpp"

int main(int argc, char* argv[])
{
    Game game;

    game.init();
    game.run();
    game.shutdown();

    return 0;
}