//
// Created by Norm on 9/16/2025.
//

#ifndef TUTORIAL_1_WORLD_H
#define TUTORIAL_1_WORLD_H
#include <memory>
#include <vector>

#include "AnimationSystem.h"
#include "CollisionSystem.h"
#include "Component.h"
#include "Entity.h"
#include "EventManager.h"
#include "KeyboardInputSystem.h"
#include "Map.h"
#include "MovementSystem.h"
#include "RenderSystem.h"

class World {
    Map map;

    std::vector<std::unique_ptr<Entity>> entities;

    MovementSystem movementSystem;
    RenderSystem renderSystem;
    KeyboardInputSystem keyboardInputSystem;
    CollisionSystem collisionSystem;
    AnimationSystem animationSystem;
    EventManager eventManager;

public:
    World();
    void update(float dt, SDL_Event& event) {
        keyboardInputSystem.update(entities, event);
        movementSystem.update(entities, dt);
        collisionSystem.update(*this);
        animationSystem.update(entities, dt);
        cleanup();
    }
    void render() {
        map.draw();
        renderSystem.render(entities);
    }

    Entity& createEntity() {
        // we use emplace instead of push so we don't create a copy
        entities.emplace_back(std::make_unique<Entity>());
        return *entities.back();
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

    EventManager& getEventManager() { return eventManager; }

    Map& getMap() { return map; }

};


#endif //TUTORIAL_1_WORLD_H
