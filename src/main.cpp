#include <iostream>
#include "Game.h"

Game *game = nullptr;

int main() {
    const int FPS = 60;
    const float desiredFrameTime = 1000.0f / FPS; // 16.67ms per frame

    game = new Game();
    game->init("8552 Tutorial Engine", 800, 600, false);

    Uint64 lastTime = SDL_GetTicks();

    while (game->running()) {
        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f; // Convert to seconds
        lastTime = currentTime;

        game->handleEvents();
        game->update(deltaTime);
        game->render();

        // Frame limiter
        Uint64 frameTime = SDL_GetTicks() - currentTime;
        if (desiredFrameTime > frameTime) {
            SDL_Delay(static_cast<Uint32>(desiredFrameTime - frameTime));
        }
    }

    delete game;
    return 0;
}