//
// Created by Norm on 9/9/2025.
//

#ifndef TUTORIAL_1_GAMEOBJECT_H
#define TUTORIAL_1_GAMEOBJECT_H

#include "Game.h"

class GameObject {
public:
    GameObject(const char* path, int x, int y);
    ~GameObject();

    void update(float deltaTime);
    void draw();

private:
    float xPos{}, yPos{};

    SDL_Texture* texture = nullptr;
    SDL_FRect srcRect{}, dstRect{};
};

#endif //TUTORIAL_1_GAMEOBJECT_H
