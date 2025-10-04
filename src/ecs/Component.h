//
// Created by Norm on 9/16/2025.
//

#ifndef TUTORIAL_1_COMPONENT_H
#define TUTORIAL_1_COMPONENT_H

#include "SDL3/SDL_render.h"
#include "Vector2D.h"
#include <string>

// Remember that components are just data...

struct Transform {
    Vector2D position{};
    float rotation{};
    float scale{};
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

#endif //TUTORIAL_1_COMPONENT_H
