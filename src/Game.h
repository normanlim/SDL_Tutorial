//
// Created by Norm on 9/2/2025.
//

//#ifndef TUTORIAL_1_GAME_H
//#define TUTORIAL_1_GAME_H
//
//#endif //TUTORIAL_1_GAME_H

#pragma once
#include <SDL3/SDL.h>
#include "World.h"

class Game {
public:
    Game();
    ~Game();

    // These are the types that SDL uses
    void init(const char* title, int width, int height, bool fullscreen);

    // game loop functions (handleEvents, update, render)
    void handleEvents(); // checks for input and system events
    void update(); // handles the drawing of the current game state to the screen
    void render(); // handles the drawing of the current game state to the screen

    // used to free resources (destructor)
    void destroy();

    bool running() {
        return isRunning; // Just for security reasons, we do not want to accidentally change.
        // This way we can only read to it not write
    }

    World world;

    SDL_Renderer* renderer = nullptr;

private:
    int frameCount = 0;
    bool isRunning = false;

    SDL_Window* window = nullptr; // pointer because where we use it, it will return a pointer
    SDL_Event event;


    // sdl stores color channels as 8-bit unsigned (range is 0-255)
    Uint8 r,g,b,a;
};