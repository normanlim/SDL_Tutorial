//
// Created by Norm on 9/9/2025.
//

#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char *path, int x, int y) :
xPos(x), yPos(y), texture(TextureManager::load(path))
{}

GameObject::~GameObject() {
    if (texture) SDL_DestroyTexture(texture);
}

void GameObject::update(float deltaTime) {

    // assignment
      float speed = 50.0f;
//    double lastTime = 0;
//    Uint64 now = SDL_GetPerformanceCounter();
//    //double deltaTime = (double)((now - lastTime) / (double)SDL_GetPerformanceFrequency());
//    lastTime = now;

    // Move Game Object 1 pixel on x and y each frame. (NEED TO CHANGE FOR ASSIGNMENT)
    xPos += deltaTime * speed;
    yPos += deltaTime * speed;

    // Where do we want to crop the texture from
    srcRect.x = srcRect.y = 0;

    // How much to crop?
    srcRect.w = srcRect.h = 32;

    // Where to draw it?
    dstRect.x = xPos;
    dstRect.y = yPos;

    // What size to render ?
    dstRect.h = srcRect.h;
    dstRect.w = srcRect.w;
}

void GameObject::draw() {
    TextureManager::draw(texture, srcRect, dstRect);
}

