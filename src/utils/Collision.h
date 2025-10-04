//
// Created by Norm on 10/3/2025.
//

#ifndef TUTORIAL_1_COLLISION_H
#define TUTORIAL_1_COLLISION_H
#include <SDL3/SDL_rect.h>

#include "Component.h"


class Collision {

public:
    static bool AABB(const SDL_FRect& rectA, const SDL_FRect& rectB);
    static bool AABB(const Collider& colA, const Collider& colB);



};

#endif //TUTORIAL_1_COLLISION_H