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

    // Parse all object groups by name (order-independent)
    for (auto* objectGroup = mapNode->FirstChildElement("objectgroup");
         objectGroup != nullptr;
         objectGroup = objectGroup->NextSiblingElement("objectgroup"))
    {
        const char* groupName = objectGroup->Attribute("name");

        if (!groupName) {
            // Skip object groups without names
            continue;
        }

        // Check which type of object group this is
        if (strcmp(groupName, "Collision Layer") == 0) {
            // Parse collider data
            for (auto* obj = objectGroup->FirstChildElement("object");
                 obj != nullptr;
                 obj = obj->NextSiblingElement("object"))
            {
                Collider c;
                c.rect.x = obj->FloatAttribute("x");
                c.rect.y = obj->FloatAttribute("y");
                c.rect.w = obj->FloatAttribute("width");
                c.rect.h = obj->FloatAttribute("height");
                colliders.push_back(c);
            }
        }
        else if (strcmp(groupName, "SpawnPoint Layer") == 0 ||
                 strcmp(groupName, "Item Layer") == 0) {
            // Parse spawn points (handles both "SpawnPoint Layer" and "Item Layer")
            for (auto* obj = objectGroup->FirstChildElement("object");
                 obj != nullptr;
                 obj = obj->NextSiblingElement("object"))
            {
                SpawnPoint sp;
                sp.x = obj->FloatAttribute("x");
                sp.y = obj->FloatAttribute("y");
                spawnPoints.push_back(sp);
            }
        }

        // else if (strcmp(groupName, "Enemy Layer") == 0) {
        //     // Parse x?
        // }
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