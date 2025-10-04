//
// Created by Norm on 10/3/2025.
//

#include "CollisionSystem.h"

#include <iostream>

#include "Collision.h"
#include "World.h"


// Has 2 important functions but they are related.
// 1) Positions the collider with the transforms
// 2) Checking for collisions

void CollisionSystem::update(World &world) {

     // Get a list of entities that have colliders and transforms
     const std::vector<Entity*> collidables = queryCollidables(world.getEntities());

     // Outer loop
     for (size_t i = 0; i < collidables.size(); i++) {
          // Update the collider position
          auto entityA = collidables[i];
          auto& t = entityA->getComponent<Transform>();
          auto& colliderA = entityA->getComponent<Collider>();

          colliderA.rect.x = t.position.x;
          colliderA.rect.y = t.position.y;


          // Check for collider collision
          // Inner loop
          for (size_t j = i+1; j < collidables.size(); j++) {
               auto entityB = collidables[j];
               auto& colliderB = entityB->getComponent<Collider>();

               if (Collision::AABB(colliderA, colliderB)) {
                    // std::cout << colliderA.tag <<  " hit " << colliderB.tag << std::endl;
                    world.getEventManager().emit(CollisionEvent(entityA, entityB));
               }
          }
     }
}


std::vector<Entity*> CollisionSystem::queryCollidables(const std::vector<std::unique_ptr<Entity>>& entities) {
     std::vector<Entity*> collidables;
     for (auto& e : entities) {
          if (e->hasComponent<Transform>() && e->hasComponent<Collider>()) {
               collidables.push_back(e.get());
          }
     }

     return collidables;
}