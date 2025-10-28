//
// Created by Norm on 9/2/2025.
//
#include <iostream>
#include <iomanip>
#include <vector>
#include "Game.h"

#include "manager/AssetManager.h"
#include "Map.h"
//#include "GameObject.h"

// Map *map = nullptr; // removed lecture 6
//GameObject *player = nullptr;


std::function<void(std::string)> Game::onSceneChangeRequest;

Game::Game() {}

Game::~Game() {
    destroy();
}

// Color structure to hold RGBA values
struct Color {
    Uint8 r, g, b, a;
    Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255)
            : r(red), g(green), b(blue), a(alpha) {}
};

// List of colors to cycle through
std::vector<Color> colors = {
        Color(100, 255, 50),   // Green
        Color(255, 100, 100),  // Red
        Color(100, 100, 255),  // Blue
        Color(255, 255, 100),  // Yellow
        Color(255, 100, 255),  // Magenta
        Color(100, 255, 255),  // Cyan
        Color(255, 165, 0),    // Orange
        Color(128, 0, 128)     // Purple
};

int currentColorIndex = 0;
Uint32 lastColorChange = 0;
const Uint32 COLOR_CHANGE_INTERVAL = 1000; // Change color every 1000ms (1 second)
float lastFrameTime = 0.0;
float currentFrameTime = 0.0f;

void Game::init(const char *title, int width, int height, bool fullscreen) {

    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    //Initalize SDL library
    if (SDL_InitSubSystem((SDL_INIT_VIDEO) == 1)) {
        std::cout << "Subsystem initalized..." << std::endl;
        window = SDL_CreateWindow(title, width, height, flags);
        if (window) {
            std::cout << "Window created..." << std::endl;
        }

        // Depends on your OS, or whatever you define. Windows will be Direct3D, Mac will be Metal.
        renderer = SDL_CreateRenderer(window, nullptr); // Creates Rendering context

        if (renderer) {
            std::cout << "Renderer created..." << std::endl;
        } else {
            std::cout << "Render could not be created." << std::endl;
            return;
        }

        isRunning = true;
    }
    else {
        isRunning = false;
    }

    // Loads assets
    AssetManager::loadAnimation("player","../asset/animations/piggy_animations.xml");
    AssetManager::loadAnimation("enemy","../asset/animations/bird_animations.xml");

std::cout << "loaded assets" << std::endl;

    // Load Scenes
    sceneManager.loadScene("level1","../asset/map.tmx", width, height);
    sceneManager.loadScene("level2", "../asset/map2.tmx", width, height);

    // Start level 1
    sceneManager.changeSceneDeferred("level1");

    // Resolve scene callback
    onSceneChangeRequest = [this](std::string sceneName) {

        if (sceneManager.currentScene->getName() == "level2" && sceneName == "level2") {
            std::cout << "You win! - Game Over" << std::endl;
            isRunning = false;
            return;
        }

        if (sceneName == "gameover") {
            isRunning = false;
            return;
        }

        sceneManager.changeSceneDeferred(sceneName);
    };


    // Assignment 4 validation (need to print?)
    // Vector2D a(3, 4);
    // Vector2D b(1, 2);
    //
    // a += b;              // a is now (4, 6)
    // Vector2D c = a - b;  // c is (3, 4)
    // Vector2D d = a * 2;  // d is (8, 12)
    // Vector2D e = 2 * a;  // e is also (8, 12)
    // Vector2D f = -a;     // f is (-4, -6)
    // bool same = (a == b); // false



}

void Game::handleEvents() {

    // SDL listens to the OS for input events internally, and it adds them to a queue

    //SDL_Event event;
    SDL_PollEvent(&event); // Check for next event, if event available, it will remove from the queue and store in event

    switch (event.type) {
        case SDL_EVENT_QUIT: // usually triggered when the user closes the window
        isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update(float dt) {
    sceneManager.update(dt, event);
}

void Game::render() {

    ///////////////////////////////////////////////////////////////////////////////////////
    // Get current time

//    // Check if it's time to change color
//    if (currentTime - lastColorChange > COLOR_CHANGE_INTERVAL) {
//        currentColorIndex = (currentColorIndex + 1) % colors.size();
//        lastColorChange = currentTime;
//    }

    // Get current color from the list
    // Color currentColor = colors[currentColorIndex];
    ///////////////////////////////////////////////////////////////////////////////////////

//    SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);
//    SDL_RenderClear(renderer); // every frame the renderer is cleared with the draw color

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer); // every frame the renderer is cleared with the draw color

    // All your drawing will go here...
    // map->draw();
    //player->draw();

    // display everything that was just drawn
    // draws it in memory first to a back buffer

    // swaps the back buffer to the screen
    SDL_RenderPresent(renderer);

}

void Game::destroy() {

    TextureManager::clean();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "GameDestroyed!" << std::endl;
}

