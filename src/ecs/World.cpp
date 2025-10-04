//
// Created by Norm on 10/3/2025.
//

#include "World.h"

#include <iostream>

// Assignment 5: Free function to handle collision events (standalone function, not part of a class)
void onCollisionDetected(const CollisionEvent& collision) {
    std::cout << "A collision occurred between entity A and entity B" << std::endl;
}

World::World() {

    // Assignment 5: Subscribing to the free function above
    eventManager.subscribe<CollisionEvent>(onCollisionDetected);

    // [Tutorial Lambda] Subscribe to the collision events
    eventManager.subscribe<CollisionEvent>([](const CollisionEvent& collision){
        if (collision.entityA == nullptr || collision.entityB == nullptr) return;

        if (!collision.entityA->hasComponent<Collider>() && collision.entityB->hasComponent<Collider>()) return;

        auto& colliderA = collision.entityA->getComponent<Collider>();
        auto& colliderB = collision.entityB->getComponent<Collider>();

        Entity* player = nullptr;
        Entity* item = nullptr;

        if (colliderA.tag == "player" && colliderB.tag == "item") {
            player = collision.entityA;
            item = collision.entityB;
        }
        else if ( colliderA.tag == "item" && colliderB.tag == "player") {
            player = collision.entityB;
            item = collision.entityA;
        }

        if (player && item) {
            item->destroy();
        }
    });

}
