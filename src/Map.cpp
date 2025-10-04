//
// Created by Norm on 9/9/2025.
//

#include "Map.h"
#include "TextureManager.h"

int mapData[10][15] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
        {0,0,1,1,1,2,2,2,1,1,1,1,0,0,0},
        {0,0,1,1,1,2,2,2,2,2,1,1,0,0,0},
        {0,0,1,1,1,2,2,2,2,2,1,1,0,0,0},
        {0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

Map::Map() :
water(TextureManager::load("../asset/water.png")),
dirt(TextureManager::load("../asset/dirt.png")),
grass(TextureManager::load("../asset/grass.png"))
{
    load(mapData);

    // What part of the image do we want?
    src.x = src.y = 0; // Assigns 0 to both x and y. (0,0) top left corner.
    src.w = src.h = 32;

    // Where do we want to display it?
    dest.x = dest.y = 0;

    // How big do we want to display it?
    dest.w = dest.h = 64; // Double the size or will be hard to see
}

Map::~Map() {
    if (water) SDL_DestroyTexture(water);
    if (dirt) SDL_DestroyTexture(dirt);
    if (grass) SDL_DestroyTexture(grass);
}

void Map::load(int data[10][15]) {

    // Load in data
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 15; col++) {
            map[row][col] = data[row][col];
        }
    }
}

void Map::draw() {
    int type = 0;

    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 15; col++) {
            type = map[row][col];

            dest.x = col * 64;
            dest.y = row * 64;

            switch(type) {
                case 0:
                    TextureManager::draw(water,src,dest);
                    break;

                case 1:
                    TextureManager::draw(dirt,src,dest);
                    break;

                case 2:
                    TextureManager::draw(grass,src,dest);
                    break;

                default:
                    break;
            }
        }
    }
}