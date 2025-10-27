//
// Created by Norm on 10/27/2025.
//

#ifndef TUTORIAL_1_DESTRUCTIONSYSTEM_H
#define TUTORIAL_1_DESTRUCTIONSYSTEM_H

#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

class DestructionSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities) {

        Entity* cameraEntity = nullptr;

        // find camera
        for (auto& e: entities) {
            if (e->hasComponent<Camera>()) {
                cameraEntity = e.get();
                break;
            }
        }

        if (!cameraEntity) return;
        auto& cam = cameraEntity->getComponent<Camera>();

        for (auto& e: entities) {
            if (e->hasComponent<Transform>() && e->hasComponent<ProjectileTag>()) {
                auto& t = e->getComponent<Transform>();

                // Destroy entity if it goes out the cam view
                if (
                    t.position.x > cam.view.x + cam.view.w ||   // right edge
                    t.position.x < cam.view.x ||                // left edge
                    t.position.y > cam.view.y + cam.view.h ||   // bottom edge
                    t.position.y < cam.view.y                   // top edge
                ) {
                    e->destroy();
                }
            }
        }
    }
};

#endif //TUTORIAL_1_DESTRUCTIONSYSTEM_H