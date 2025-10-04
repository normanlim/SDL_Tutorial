#include <iostream>

#include "Game.h"

Game *game = nullptr;

int main() {

    const int FPS = 60; // 60 is the closest refresh rate of most our monitors, 30 fps is the halfway point
    const int desiredFrameTime = 100 / FPS; // 16ms per frame

    Uint64 ticks;
    int actualFrameTime;

    game = new Game(); // created on the heap, we will need to clean this up!! very important
    game -> init("8552 Tutorial Engine", 800, 600, false);

    while ( game -> running() ) {
        ticks = SDL_GetTicks(); // time in milliseconds since we initialized SDL

        game -> handleEvents();
        game -> update();
        game -> render();

        actualFrameTime = SDL_GetTicks(); // elapsed time in ms to run the above 3 functions (depends on hardware)

        // frame limiter for strong PC's that get more than 60 FPS
        if (desiredFrameTime > actualFrameTime) { // if actual frame took less time than desired frame, delay difference
            SDL_Delay(desiredFrameTime - actualFrameTime);
        }
    }

    delete game;

    return 0;
}
