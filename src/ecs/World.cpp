//
// Created by Norm on 10/3/2025.
//

#include "World.h"

#include <iostream>

#include "Game.h"

// Assignment 5: Free function to handle collision events (standalone function, not part of a class)
void onCollisionDetected(const CollisionEvent& collision) {
    // std::cout << "A collision occurred between entity A and entity B" << std::endl;
}

World::World() {

    // Assignment 5: Subscribing to the free function above
    eventManager.subscribe(onCollisionDetected);

    // [Tutorial Lambda] Subscribe to the collision events
    eventManager.subscribe([this](const CollisionEvent& collision){

        Entity* sceneStateEntity = nullptr;

        // Find scene state
        for (auto& e:entities) {
            if (e->hasComponent<SceneState>()) {
                sceneStateEntity = e.get();
                break;
            }
        }

        if (!sceneStateEntity) return;

        if (collision.entityA == nullptr || collision.entityB == nullptr) return;

        if (!collision.entityA->hasComponent<Collider>() &&  collision.entityB->hasComponent<Collider>()) return;

        auto& colliderA = collision.entityA->getComponent<Collider>();
        auto& colliderB = collision.entityB->getComponent<Collider>();

        Entity* player = nullptr;
        Entity* item = nullptr;
        Entity* wall = nullptr;
        Entity* projectile = nullptr;

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

            // Scene state!
            auto& sceneState = sceneStateEntity->getComponent<SceneState>();
            sceneState.coinsCollected++;

            if (sceneState.coinsCollected > 1) {
                Game::onSceneChangeRequest("level2");
            }

        }

        // Player vs wall
        if (colliderA.tag == "player" && colliderB.tag == "wall") {
            player = collision.entityA;
            wall = collision.entityB;
        }
        else if ( colliderA.tag == "wall" && colliderB.tag == "player") {
            player = collision.entityB;
            wall = collision.entityA;
        }

        if (player && wall) {
            // Stop the player
            auto& t = player->getComponent<Transform>();
            t.position = t.oldPosition;
        }


        // Player vs projectile
        if (colliderA.tag == "player" && colliderB.tag == "projectile") {
            player = collision.entityA;
            projectile = collision.entityB;
        }
        else if ( colliderA.tag == "projectile" && colliderB.tag == "player") {
            player = collision.entityB;
            projectile = collision.entityA;
        }

        if (player && projectile) {
            player->destroy();

            Game::onSceneChangeRequest("gameover");
        }


    });

}
