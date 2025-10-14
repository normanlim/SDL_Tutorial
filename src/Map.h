//
// Created by Norm on 9/9/2025.
//

#ifndef TUTORIAL_1_MAP_H
#define TUTORIAL_1_MAP_H

#include <vector>
#include <SDL3/SDL.h>
#include <Component.h>

struct SpawnPoint {
    float x;
    float y;
};

class Map {
public:
    Map() = default;
    ~Map() = default;


    // void load(int data[10][15]); // no longer using hard-coded data
    void load(const char* path, SDL_Texture *ts);
    void draw(const Camera& cam);

    SDL_Texture *tileset = nullptr;
    int width{}, height{};
    std::vector<std::vector<int>> tileData;
    std::vector<Collider> colliders;

    // Assignment 6...
    std::vector<SpawnPoint> spawnPoints;

private:

    // No longer needed (Tutorial 6)
    // SDL_FRect src{}, dest{}; // Brace initaliztion, all members in struct will be initalized as ZERO (0)
    // SDL_Texture* water = nullptr;
    // SDL_Texture* dirt = nullptr;
    // SDL_Texture* grass = nullptr;
    //
    // int map[10][15]{};


};

#endif //TUTORIAL_1_MAP_H
