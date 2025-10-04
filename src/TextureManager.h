//
// Created by Norm on 9/9/2025.
//

#ifndef TUTORIAL_1_TEXTUREMANAGER_H
#define TUTORIAL_1_TEXTUREMANAGER_H

#include <unordered_map>

#include "SDL3_image/SDL_image.h"

class TextureManager {

    static std::unordered_map<std::string, SDL_Texture*> textures;

public:
    static SDL_Texture* load(const char* path);
    static void draw(SDL_Texture* texture, SDL_FRect src, SDL_FRect dst); // x,y,width,height // floating point Rect = FRect
    static void clean();

};

#endif //TUTORIAL_1_TEXTUREMANAGER_H
