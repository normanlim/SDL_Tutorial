//
// Created by Norm on 9/9/2025.
//

#include <iostream>
#include <ostream>
#include "TextureManager.h"
#include "Game.h"


// Doesn't create any extra memory, just grabs the reference of this object that was created in Game.cpp
extern Game* game;

std::unordered_map<std::string, SDL_Texture*> TextureManager::textures;

// Load our texture with a path
SDL_Texture* TextureManager::load(const char* path) {

    // Caching: storing the result of some work so you don't have to repeat the work next time.
    // Check if the texture already exists in the map.
    auto it = textures.find(path);
    if (it != textures.end()) { // if the iterator is not at the end we found it
        return it->second;
    }


    // A surface represents an image in RAM (CPU Memory). Do we want to do anything with the image before store in GPU
    SDL_Surface* tempSurface = IMG_Load(path);
    if (!tempSurface) {
        std::cout << "Failed to load image: " << path << std::endl;
    }

    // A texture represents an image in VRAM (GPU Memory)
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, tempSurface);

    // Cleanup surface
    SDL_DestroySurface(tempSurface);

    // Check if the texture creation was successful
    if (!texture) {
        std::cout << "Failed to create texture: " << path << std::endl;
        return nullptr;
    }

    // Store the new texture in the cache
    textures[path] = texture;

    return texture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_FRect src, SDL_FRect dst) {

    // Draw the texture from the screen to the VRAM
    SDL_RenderTexture(game->renderer, texture, &src, &dst);
}


void TextureManager::clean() {
    for (auto& tex: textures) {
        SDL_DestroyTexture(tex.second);
        tex.second = nullptr;
    }
    textures.clear();
}