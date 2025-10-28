//
// Created by Norm on 10/27/2025.
//

#ifndef TUTORIAL_1_SCENEMANAGER_H
#define TUTORIAL_1_SCENEMANAGER_H
#include <iostream>
#include <memory>
#include <unordered_map>

#include "Scene.h"

struct SceneParams {
    const char* name;
    const char* mapPath;
    int windowWidth;
    int windowHeight;
};

class SceneManager {
    std::unordered_map<std::string, SceneParams> sceneParam;
    std::string pendingScene;

    void changeScene(const std::string& name) {
        auto it = sceneParam.find(name);
        if (it != sceneParam.end()) {
            const auto& params = it->second;

            // Create scene object (AKA BUILD SCENE)
            currentScene = std::make_unique<Scene>(params.name, params.mapPath, params.windowWidth, params.windowHeight);
        }
        else {
            std::cerr << "Scene " << name << " not found!" << std::endl;
        }
    }

public:
    std::unique_ptr<Scene> currentScene;
    void loadScene(const char* sceneName, const char* mapPath, const int windowWidth, const int windowHeight) {
        sceneParam[sceneName] = { sceneName, mapPath, windowWidth, windowHeight};
    }

    void changeSceneDeferred(const std::string& name) {
        pendingScene = name;
    }

    void update(const float dt, const SDL_Event &e) {
        if (currentScene) currentScene->update(dt, e);  // all our world updates
        if (!pendingScene.empty()) {
            changeScene(pendingScene);
            pendingScene.clear();
        }
    }

    void render() const {
        if (currentScene) currentScene->render();
    }
};

#endif //TUTORIAL_1_SCENEMANAGER_H