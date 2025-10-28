//
// Created by Norm on 10/14/2025.
//

#ifndef TUTORIAL_1_ASSETMANAGER_H
#define TUTORIAL_1_ASSETMANAGER_H
#include <unordered_map>

#include "Component.h"

class AssetManager {

    static std::unordered_map<std::string, Animation> animations;
    static Animation loadAnimationFromXML(const char *path);

public:
    static void loadAnimation(const std::string& clipName, const char *path);
    static const Animation& getAnimation(const std::string& clipName);


};

#endif //TUTORIAL_1_ASSETMANAGER_H