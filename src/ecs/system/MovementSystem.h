//
// Created by Norm on 9/16/2025.
//

#ifndef TUTORIAL_1_MOVEMENTSYSTEM_H
#define TUTORIAL_1_MOVEMENTSYSTEM_H

#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

class MovementSystem {
public:
    void update(std::vector<std::unique_ptr<Entity>>& entities, float dt) {
        for (auto& entity : entities) {
            if (entity->hasComponent<Transform>() && entity->hasComponent<Velocity>()) {
                auto& tr = entity->getComponent<Transform>();
                auto& ve = entity->getComponent<Velocity>();
                // tr.position.x += 60 * dt;
                // tr.position.y += 60* dt; // no longer need code to move diagnoally, doing input based movement now

                // Check previous frame's position
                tr.oldPosition = tr.position;

                Vector2D directionVec = ve.direction;

                // normalizing magnitude (didnt happen yet)
                directionVec.normalize();

                // Vector2D needs an operator function to multiply a float to itself
                Vector2D velocityVec = directionVec * ve.speed;
                Vector2D velocityVec_2 = ve.speed * directionVec;

                tr.position += (velocityVec * dt);

            }
        }
    }
};

#endif //TUTORIAL_1_MOVEMENTSYSTEM_H
