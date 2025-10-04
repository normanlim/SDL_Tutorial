//
// Created by Norm on 9/9/2025.
//

#ifndef TUTORIAL_1_MAP_H
#define TUTORIAL_1_MAP_H

#include "Game.h"

class Map {
public:
    Map();
    ~Map();

    void load(int data[10][15]);
    void draw();

private:
    SDL_FRect src{}, dest{}; // Brace initaliztion, all members in struct will be initalized as ZERO (0)
    SDL_Texture* water = nullptr;
    SDL_Texture* dirt = nullptr;
    SDL_Texture* grass = nullptr;

    int map[10][15]{};


};

#endif //TUTORIAL_1_MAP_H
