//
// Created by Norm on 9/9/2025.
//

#include "Map.h"

#include <cmath>

#include "TextureManager.h"
#include <sstream>
#include <tinyxml2.h>


void Map::load(const char *path, SDL_Texture *ts) {
    tileset = ts;
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path);

    // Parse width and height of map
    auto* mapNode = doc.FirstChildElement("map");
    width = mapNode->IntAttribute("width");
    height = mapNode->IntAttribute("height");

    // Parse terrain data
    auto* layer = mapNode->FirstChildElement("layer");
    auto* data = layer->FirstChildElement("data");
    std::string csv = data->GetText();
    std::stringstream ss(csv);
    tileData = std::vector(height, std::vector<int>(width));

    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            std::string val;

            // Read characters from a stringstream into val until it hits a comma, or is at the end of the stream
            if (!std::getline(ss, val, ',')) break;
            tileData[i][j] = std::stoi(val);
        }
    }

    // Parse collider data
    auto* objectGroup = layer->NextSiblingElement("objectgroup");
    // create for loop with initialization , condition, and increment.
    for ( auto* obj= objectGroup->FirstChildElement("object");
          obj != nullptr;
          obj = obj->NextSiblingElement("object")
        )
    {
        Collider c;
        c.rect.x = obj->FloatAttribute("x");
        c.rect.y = obj->FloatAttribute("y");
        c.rect.w = obj->FloatAttribute("width");
        c.rect.h = obj->FloatAttribute("height");
        colliders.push_back(c);
    }

    // Parse spawn points
    auto* spawnPointGroup = objectGroup->NextSiblingElement("objectgroup");
    if (spawnPointGroup) {
        for (auto* obj = spawnPointGroup->FirstChildElement("object");
             obj != nullptr;
             obj = obj->NextSiblingElement("object"))
        {
            SpawnPoint sp;
            sp.x = obj->FloatAttribute("x");
            sp.y = obj->FloatAttribute("y");
            spawnPoints.push_back(sp);
        }
    }

}

void Map::draw(const Camera& cam) {

    SDL_FRect src{}, dest{};

    dest.w = dest.h = 32; // Note, can do it dynamically from file too like above

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int type = tileData[row][col];

            // Move the tiles or map relative to the camera, convert from world space to screen space.
            float worldX = static_cast<float>(col) * dest.w;
            float worldY = static_cast<float>(row) * dest.h;

            dest.x = std::round(worldX - cam.view.x);
            dest.y = std::round(worldY - cam.view.y);

            switch(type) {
                case 1:
                    // Dirt
                    src.x = 0;
                    src.y = 0;
                    src.w = 32;
                    src.h = 32;
                    break;

                case 2:
                    // Grass
                    src.x = 32;
                    src.y = 0;
                    src.w = 32;
                    src.h = 32;
                    break;

                case 4:
                    // Water
                    src.x = 32;
                    src.y = 32;
                    src.w = 32;
                    src.h = 32;
                    break;

                default:
                    break;
            }

            TextureManager::draw(tileset, src, dest);
        }
    }
}





// No longer needed (Tutorial 6) ... everything below

// int mapData[10][15] = {
//         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//         {0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
//         {0,0,1,1,1,2,2,2,1,1,1,1,0,0,0},
//         {0,0,1,1,1,2,2,2,2,2,1,1,0,0,0},
//         {0,0,1,1,1,2,2,2,2,2,1,1,0,0,0},
//         {0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
//         {0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
//         {0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
//         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
// };

// Map::Map() :
// water(TextureManager::load("../asset/water.png")),
// dirt(TextureManager::load("../asset/dirt.png")),
// grass(TextureManager::load("../asset/grass.png"))
// {
//     load(mapData);
//
//     // What part of the image do we want?
//     src.x = src.y = 0; // Assigns 0 to both x and y. (0,0) top left corner.
//     src.w = src.h = 32;
//
//     // Where do we want to display it?
//     dest.x = dest.y = 0;
//
//     // How big do we want to display it?
//     dest.w = dest.h = 64; // Double the size or will be hard to see
// }
//
// Map::~Map() {
//     if (water) SDL_DestroyTexture(water);
//     if (dirt) SDL_DestroyTexture(dirt);
//     if (grass) SDL_DestroyTexture(grass);
// }
//
// void Map::load(int data[10][15]) {
//
//     // Load in data
//     for (int row = 0; row < 10; row++) {
//         for (int col = 0; col < 15; col++) {
//             map[row][col] = data[row][col];
//         }
//     }
// }
//
// void Map::draw() {
//     int type = 0;
//
//     for (int row = 0; row < 10; row++) {
//         for (int col = 0; col < 15; col++) {
//             type = map[row][col];
//
//             dest.x = col * 64;
//             dest.y = row * 64;
//
//             switch(type) {
//                 case 0:
//                     TextureManager::draw(water,src,dest);
//                     break;
//
//                 case 1:
//                     TextureManager::draw(dirt,src,dest);
//                     break;
//
//                 case 2:
//                     TextureManager::draw(grass,src,dest);
//                     break;
//
//                 default:
//                     break;
//             }
//         }
//     }
// }
