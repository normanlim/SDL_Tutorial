//
// Created by Norm on 10/27/2025.
//

#ifndef TUTORIAL_1_SPAWNTIMERSYSTEM_H
#define TUTORIAL_1_SPAWNTIMERSYSTEM_H

#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

class SpawnTimerSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities, const float dt) {
        for (auto& entity: entities) {
            if (entity->hasComponent<TimedSpawner>()) {
                auto& spawner = entity->getComponent<TimedSpawner>();

                spawner.timer -= dt;

                if (spawner.timer <= 0) {
                    spawner.timer = spawner.spawnInterval; // (eg 2 seconds)
                    spawner.spawnCallback(); // create entity inside here
                }
            }
        }
    }
};

#endif //TUTORIAL_1_SPAWNTIMERSYSTEM_H