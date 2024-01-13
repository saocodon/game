#define SDL_MAIN_HANDLED
#include "core/game.hpp"

int main(int argc, char* argv[])
{
    Game* game = new Game();
    game->init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    Uint32 frameStart;
    int frameTime;
    while (game->running()) {
        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
    game->clean();
    return 0;
}