//
// Created by Norm on 9/2/2025.
//
#include <iostream>
#include <iomanip>
#include <vector>
#include "Game.h"

#include "AssetManager.h"
#include "Map.h"
//#include "GameObject.h"

// Map *map = nullptr; // removed lecture 6
//GameObject *player = nullptr;

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

    AssetManager::loadAnimation("player","../asset/animations/piggy_animations.xml");
    AssetManager::loadAnimation("enemy","../asset/animations/bird_animations.xml");


    // Load our map
    world.getMap().load("../asset/map.tmx", TextureManager::load("../asset/tileset.png"));

    // Add colliders
    for (auto &collider : world.getMap().colliders) {
        auto& e = world.createEntity();
        e.addComponent<Transform>(Vector2D(collider.rect.x, collider.rect.y), 0.0f, 1.0f);
        auto& c = e.addComponent<Collider>("no-wall");
        c.rect.x = collider.rect.x;
        c.rect.y = collider.rect.y;
        c.rect.w = collider.rect.w;
        c.rect.h = collider.rect.h;

        // Just to have a visual of the colliders.
        SDL_Texture* tex = TextureManager::load("../asset/tileset.png");
        SDL_FRect colSrc { 0,32,32,32 };
        SDL_FRect colDst { c.rect.x, c.rect.y, c.rect.w, c.rect.h };
        e.addComponent<Sprite>(tex,colSrc,colDst);

    }

    // Add coins from our map
    SDL_Texture* coinTex = TextureManager::load("../asset/coin.png");
    for (auto& spawnPoint : world.getMap().spawnPoints) {
        auto& item(world.createEntity());
        auto& itemTransform = item.addComponent<Transform>(Vector2D(spawnPoint.x, spawnPoint.y), 0.0f, 1.0f);

        SDL_FRect itemSrc { 0,0,32,32 };
        SDL_FRect itemDest { itemTransform.position.x, itemTransform.position.y, 32, 32 };
        item.addComponent<Sprite>(coinTex, itemSrc, itemDest);

        auto& itemCollider = item.addComponent<Collider>("item");
        itemCollider.rect.w = itemDest.w;
        itemCollider.rect.h = itemDest.h;
    }



    // map = new Map(); // Removed lecture 6
    //player = new GameObject("../asset/ball.png", 0, 0);

    // Add entities
    // auto& item(world.createEntity());
    // auto& itemTransform = item.addComponent<Transform>(Vector2D(200,100), 0.0f, 1.0f);
    //
    // SDL_Texture* itemTex = TextureManager::load("../asset/coin.png");
    // SDL_FRect itemSrc { 0,0,32,32 };
    //
    // SDL_FRect itemDest { itemTransform.position.x, itemTransform.position.y, 32, 32 };
    // item.addComponent<Sprite>(itemTex, itemSrc, itemDest);
    //
    // auto& itemCollider = item.addComponent<Collider>("item");
    // itemCollider.rect.w = itemDest.w;
    // itemCollider.rect.h = itemDest.h;


    // Add our camera
    auto& cam = world.createEntity();
    SDL_FRect camView{};
    camView.w = width;
    camView.h = height;
    cam.addComponent<Camera>(camView, world.getMap().width * 32, world.getMap().height * 32);


    auto& player(world.createEntity());
    auto& playerTransform = player.addComponent<Transform>(Vector2D(0,0), 0.0f, 1.0f);
    player.addComponent<Velocity>(Vector2D(0.0f, 0.0f), 120.0f); // Add number here for initial velocity on gameload

    Animation anim = AssetManager::getAnimation("player");
    player.addComponent<Animation>(anim);

    SDL_Texture* tex = TextureManager::load("../asset/animations/piggy_anim.png");
    // SDL_FRect playerSrc { 0,0,32,44};
    SDL_FRect playerSrc = anim.clips[anim.currentClip].frameIndicies[0]; // new one for bull
    SDL_FRect playerDst { playerTransform.position.x, playerTransform.position.y, 64, 64};

    player.addComponent<Sprite>(tex, playerSrc, playerDst);

    auto& playerCollider = player.addComponent<Collider>("player");
    playerCollider.rect.w = playerDst.w;
    playerCollider.rect.h = playerDst.h;

    player.addComponent<PlayerTag>();


    /////

    std::cout << "Creating spawner entity..." << std::endl;
    auto& spawner(world.createEntity());
    std::cout << "Adding Transform to spawner..." << std::endl;
    Transform t = spawner.addComponent<Transform>(Vector2D(width/2, height-5), 0.0f, 1.0);
    std::cout << "Transform added at: " << t.position.x << ", " << t.position.y << std::endl;

    std::cout << "Adding TimedSpawner component..." << std::endl;
    spawner.addComponent<TimedSpawner>(2.0f, [this, t] {
        std::cout << "SPAWNER CALLBACK TRIGGERED!" << std::endl;
        std::cout << "Creating deferred entity..." << std::endl;

        auto& e(world.createDeferredEntity());
        std::cout << "Adding transform to projectile at: " << t.position.x << ", " << t.position.y << std::endl;
        e.addComponent<Transform>(Vector2D(t.position.x, t.position.y), 0.0f, 1.0f);
        e.addComponent<Velocity>(Vector2D(0,-1), 100.0f);

        std::cout << "Loading animation..." << std::endl;
        Animation anim = AssetManager::getAnimation("enemy");
        e.addComponent<Animation>(anim);

        std::cout << "Loading texture..." << std::endl;
        SDL_Texture* tex = TextureManager::load("../asset/animations/bird_anim.png");
        SDL_FRect src {0,0,32,32};
        SDL_FRect dest {t.position.x, t.position.y, 32, 32};
        e.addComponent<Sprite>(tex,src,dest);

        std::cout << "Adding collider..." << std::endl;
        auto& c = e.addComponent<Collider>("projectile");
        c.rect.w = dest.w;
        c.rect.h = dest.h;
        e.addComponent<ProjectileTag>();

        std::cout << "Projectile created successfully!" << std::endl;
    });
    std::cout << "TimedSpawner component added!" << std::endl;



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

void Game::update() {
    auto currentTime = static_cast<double>(SDL_GetTicks());
    if (lastFrameTime == 0.0) {
        // std::cout << " in IF: "<< std::endl;

        lastFrameTime = currentTime;
    }
    float deltaTime = (currentTime - lastFrameTime) / 1000.0f;
    lastFrameTime = currentTime;

    frameCount++;
    // std::cout << std::fixed << std::setprecision(10);
    // std::cout << frameCount << " delta time: " << deltaTime << std::endl;
    //player->update(deltaTime);

    world.update(deltaTime, event);
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
    Color currentColor = colors[currentColorIndex];
    ///////////////////////////////////////////////////////////////////////////////////////

//    SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);
//    SDL_RenderClear(renderer); // every frame the renderer is cleared with the draw color

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer); // every frame the renderer is cleared with the draw color

    // All your drawing will go here...
    // map->draw();
    //player->draw();
    world.render();

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

