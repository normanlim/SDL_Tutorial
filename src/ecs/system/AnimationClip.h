//
// Created by Norm on 10/14/2025.
//

#ifndef TUTORIAL_1_ANIMATIONCLIP_H
#define TUTORIAL_1_ANIMATIONCLIP_H
#include <vector>
#include <SDL3/SDL_rect.h>

struct AnimationClip {
    std::vector<SDL_FRect> frameIndicies;
};

#endif //TUTORIAL_1_ANIMATIONCLIP_H