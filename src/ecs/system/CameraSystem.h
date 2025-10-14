//
// Created by Norm on 10/14/2025.
//

#ifndef TUTORIAL_1_CAMERASYSTEM_H
#define TUTORIAL_1_CAMERASYSTEM_H
#include "Component.h"

class CameraSystem {
    public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities) {
        Entity* playerEntity = nullptr;

        // Find the player
        for (auto& e: entities) {
            if (e->hasComponent<PlayerTag>()) {
                playerEntity = e.get();
                break;
            }
        }

        if (!playerEntity) return;

        auto& playerTransform = playerEntity->getComponent<Transform>();

        for (auto& e: entities) {
            if (e->hasComponent<Camera>()) {

                auto& cam = e->getComponent<Camera>();

                // This positions the camera so the player is at the center of its view
                cam.view.x = playerTransform.position.x - cam.view.w / 2;
                cam.view.y = playerTransform.position.y - cam.view.h / 2;

                // Clamp camera (The camera is position itself so player is centered)
                // But the player can walk off the window, so we clamp the camera to stay inside the window.
                if (cam.view.x < 0) cam.view.x = 0;
                if (cam.view.y < 0) cam.view.y = 0;
                if (cam.view.x > cam.worldWidth - cam.view.w) cam.view.x = cam.worldWidth - cam.view.w;
                if (cam.view.y > cam.worldHeight - cam.view.h) cam.view.y = cam.worldHeight - cam.view.h;

            }
        }
    }
};

#endif //TUTORIAL_1_CAMERASYSTEM_H