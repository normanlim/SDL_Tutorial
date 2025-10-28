//
// Created by Norm on 10/14/2025.
//

#include "AssetManager.h"

#include "tinyxml2.h"

std::unordered_map<std::string, Animation> AssetManager::animations;

void AssetManager::loadAnimation(const std::string &clipName, const char *path) {
    Animation animation = loadAnimationFromXML(path);
    animations[clipName] = animation;
}

const Animation& AssetManager::getAnimation(const std::string &clipName) {
    return animations[clipName];
}

Animation AssetManager::loadAnimationFromXML(const char *path) {
    Animation anim;

    tinyxml2::XMLDocument doc;
    doc.LoadFile(path);

    auto* root = doc.FirstChildElement("animations");
    for (auto* clipElem = root->FirstChildElement();
        clipElem;
        clipElem = clipElem->NextSiblingElement())
    {
        std::string clipName = clipElem->Name();
        AnimationClip clip;

        for (auto* frameElem = clipElem->FirstChildElement("frame");
            frameElem;
            frameElem = frameElem->NextSiblingElement("frame"))
        {
            SDL_FRect rect;
            frameElem->QueryFloatAttribute("x", &rect.x);
            frameElem->QueryFloatAttribute("y", &rect.y);
            frameElem->QueryFloatAttribute("w", &rect.w);
            frameElem->QueryFloatAttribute("h", &rect.h);

            clip.frameIndicies.push_back(rect);
        }

        anim.clips[clipName] = clip;

    }

    if (!anim.clips.empty()) {
        // If we actually had some entries , we are setting the current clip Default to first one.
        anim.currentClip = anim.clips.begin()->first;
    }

    return anim;
}