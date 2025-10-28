//
// Created by Norm on 10/27/2025.
//

#include "Scene.h"

#include <iostream>

#include "AssetManager.h"

Scene::Scene(const char* sceneName, const char* mapPath, const int windowWidth, const int windowHeight) : name(sceneName) {

    // Load our map
    world.getMap().load(mapPath, TextureManager::load("../asset/tileset.png"));

    // Add colliders
    for (auto &collider : world.getMap().colliders) {
        auto& e = world.createEntity();
        e.addComponent<Transform>(Vector2D(collider.rect.x, collider.rect.y), 0.0f, 1.0f);
        auto& c = e.addComponent<Collider>("no-wall");
        c.rect.x = collider.rect.x;
        c.rect.y = collider.rect.y;
        c.rect.w = collider.rect.w;
        c.rect.h = collider.rect.h;

        // Just to have a visual of the colliders.
        SDL_Texture* tex = TextureManager::load("../asset/tileset.png");
        SDL_FRect colSrc { 0,32,32,32 };
        SDL_FRect colDst { c.rect.x, c.rect.y, c.rect.w, c.rect.h };
        e.addComponent<Sprite>(tex,colSrc,colDst);

    }

    // Add coins from our map
    SDL_Texture* coinTex = TextureManager::load("../asset/coin.png");
    for (auto& spawnPoint : world.getMap().spawnPoints) {
        auto& item(world.createEntity());
        auto& itemTransform = item.addComponent<Transform>(Vector2D(spawnPoint.x, spawnPoint.y), 0.0f, 1.0f);

        SDL_FRect itemSrc { 0,0,32,32 };
        SDL_FRect itemDest { itemTransform.position.x, itemTransform.position.y, 32, 32 };
        item.addComponent<Sprite>(coinTex, itemSrc, itemDest);

        auto& itemCollider = item.addComponent<Collider>("item");
        itemCollider.rect.w = itemDest.w;
        itemCollider.rect.h = itemDest.h;
    }



    // map = new Map(); // Removed lecture 6
    //player = new GameObject("../asset/ball.png", 0, 0);

    // Add entities
    // auto& item(world.createEntity());
    // auto& itemTransform = item.addComponent<Transform>(Vector2D(200,100), 0.0f, 1.0f);
    //
    // SDL_Texture* itemTex = TextureManager::load("../asset/coin.png");
    // SDL_FRect itemSrc { 0,0,32,32 };
    //
    // SDL_FRect itemDest { itemTransform.position.x, itemTransform.position.y, 32, 32 };
    // item.addComponent<Sprite>(itemTex, itemSrc, itemDest);
    //
    // auto& itemCollider = item.addComponent<Collider>("item");
    // itemCollider.rect.w = itemDest.w;
    // itemCollider.rect.h = itemDest.h;


    // Add our camera
    auto& cam = world.createEntity();
    SDL_FRect camView{};
    camView.w = windowWidth;
    camView.h = windowHeight;
    cam.addComponent<Camera>(camView, world.getMap().width * 32, world.getMap().height * 32);


    auto& player(world.createEntity());
    auto& playerTransform = player.addComponent<Transform>(Vector2D(0,0), 0.0f, 1.0f);
    player.addComponent<Velocity>(Vector2D(0.0f, 0.0f), 120.0f); // Add number here for initial velocity on gameload

    Animation anim = AssetManager::getAnimation("player");
    player.addComponent<Animation>(anim);

    SDL_Texture* tex = TextureManager::load("../asset/animations/piggy_anim.png");
    // SDL_FRect playerSrc { 0,0,32,44};
    SDL_FRect playerSrc = anim.clips[anim.currentClip].frameIndicies[0]; // new one for bull
    SDL_FRect playerDst { playerTransform.position.x, playerTransform.position.y, 64, 64};

    player.addComponent<Sprite>(tex, playerSrc, playerDst);

    auto& playerCollider = player.addComponent<Collider>("player");
    playerCollider.rect.w = playerDst.w;
    playerCollider.rect.h = playerDst.h;

    player.addComponent<PlayerTag>();


    /////

    auto& spawner(world.createEntity());
    Transform transform = spawner.addComponent<Transform>(Vector2D(windowWidth/2, windowHeight - 5), 0.0f, 1.0f);

    Entity* spawnPtr = &spawner;

    spawner.addComponent<TimedSpawner>(2.0f, [this, spawnPtr] {
        std::cout << "Spawning" << std::endl;
        if (!spawnPtr->isActive()) return;

        auto& transform = spawnPtr->getComponent<Transform>();
        auto& e(world.createDeferredEntity());
        std::cout << "Entity created"<< std::endl;
        e.addComponent<Transform>(Vector2D(transform.position.x,transform.position.y), 0.0f, 1.0f);
        e.addComponent<Velocity>(Vector2D(0.0f, -1.0f), 150.0f);

        Animation animation = AssetManager::getAnimation("enemy");
        e.addComponent<Animation>(animation);

        SDL_Texture* texture = TextureManager::load("../asset/animations/bird_anim.png");
        SDL_FRect src = {0,0,32,32};
        SDL_FRect dest = {transform.position.x,transform.position.y,32,32};
        e.addComponent<Sprite>(texture, src, dest);

        Collider collider = e.addComponent<Collider>("projectile");
        collider.rect.w = dest.w;
        collider.rect.h = dest.h;

        e.addComponent<ProjectileTag>();

        std::cout << "Entity fully configured!" << std::endl;
    });

    // add scene state
    auto &state(world.createEntity());
    state.addComponent<SceneState>();

}
