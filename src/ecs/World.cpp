//
// Created by Norm on 10/3/2025.
//

#include "World.h"

World::World() {
    // Subscribe to the collision events
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
