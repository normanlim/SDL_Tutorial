//
// Created by Norm on 9/16/2025.
//

#ifndef TUTORIAL_1_WORLD_H
#define TUTORIAL_1_WORLD_H
#include <memory>
#include <vector>

#include "AnimationSystem.h"
#include "CameraSystem.h"
#include "CollisionSystem.h"
#include "Component.h"
#include "DestructionSystem.h"
#include "Entity.h"
#include "EventManager.h"
#include "KeyboardInputSystem.h"
#include "Map.h"
#include "MovementSystem.h"
#include "RenderSystem.h"
#include "SpawnTimerSystem.h"

class World {
    Map map;

    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Entity>> deferredEntities;


    MovementSystem movementSystem;
    RenderSystem renderSystem;
    KeyboardInputSystem keyboardInputSystem;
    CollisionSystem collisionSystem;
    AnimationSystem animationSystem;
    CameraSystem cameraSystem;
    EventManager eventManager;
    SpawnTimerSystem spawnTimerSystem;
    DestructionSystem destructionSystem;

public:
    World();
    void update(float dt, SDL_Event& event) {
        keyboardInputSystem.update(entities, event);
        movementSystem.update(entities, dt);
        collisionSystem.update(*this);
        animationSystem.update(entities, dt);
        cameraSystem.update(entities);
        spawnTimerSystem.update(entities, dt);
        destructionSystem.update(entities);
        synchronizeEntities();
        cleanup();
    }
    void render() {

        for ( auto& entity : entities ) {
            if (entity->hasComponent<Camera>()) {
                map.draw(entity->getComponent<Camera>());
                break;
            }
        }
        renderSystem.render(entities);
    }

    Entity& createEntity() {
        // we use emplace instead of push so we don't create a copy
        entities.emplace_back(std::make_unique<Entity>());
        return *entities.back();
    }

    Entity& createDeferredEntity() {
        deferredEntities.emplace_back(std::make_unique<Entity>());
        return *deferredEntities.back();
    }

    std::vector<std::unique_ptr<Entity>>& getEntities() {
        return entities;
    }

    void cleanup() {
        // use a lambda predicate to remove all inactive entities
        std::erase_if(
                entities,
                [](std::unique_ptr<Entity>& e)
                {
                    return !e->isActive();
                }
        );
    }

    void synchronizeEntities() {
        if (!deferredEntities.empty()) {
            // push back all deferred entities to the entities vector
            std::move(
                deferredEntities.begin(),
                deferredEntities.end(),
                std::back_inserter(entities)
            );
            // clearing the creation buffer
            deferredEntities.clear();
        };
    }

    EventManager& getEventManager() { return eventManager; }

    Map& getMap() { return map; }

};


#endif //TUTORIAL_1_WORLD_H
