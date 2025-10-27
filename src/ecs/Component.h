//
// Created by Norm on 9/16/2025.
//

#ifndef TUTORIAL_1_COMPONENT_H
#define TUTORIAL_1_COMPONENT_H

#include <functional>

#include "SDL3/SDL_render.h"
#include "Vector2D.h"
#include <string>
#include <unordered_map>

#include "AnimationClip.h"

// Remember that components are just data...

struct Transform {
    Vector2D position{};
    float rotation{};
    float scale{};
    Vector2D oldPosition{};
};

// Direction and speed, so we can control direction with keyboard input
struct Velocity {
    Vector2D direction{};
    float speed{};
};

// struct Position {
//     float x = 0.0f;
//     float y = 0.0f;
// };

struct Sprite {
    SDL_Texture* texture = nullptr;
    SDL_FRect src{};
    SDL_FRect dst{};
};

struct Collider {
    std::string tag;
    SDL_FRect rect{};
};

struct Animation {
    std::unordered_map<std::string, AnimationClip> clips{};
    std::string currentClip{};
    float time{}; // Time is accumulated for the current frame
    int currentFrame{}; // Index of the current frame in the clip
    float speed = 0.1f; // time per frame
};

struct Camera {
    SDL_FRect view;
    float worldWidth;
    float worldHeight;
};

struct TimedSpawner {
    float spawnInterval{};
    std::function<void()> spawnCallback;
    float timer{};
};

// Our game state, might have multiple scenes
struct SceneState {
    int coinsCollected = 0;
};

struct PlayerTag{};
struct ProjectileTag{};

#endif //TUTORIAL_1_COMPONENT_H
