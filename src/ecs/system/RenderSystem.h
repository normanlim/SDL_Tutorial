//
// Created by Norm on 9/16/2025.
//

#ifndef TUTORIAL_1_RENDERSYSTEM_H
#define TUTORIAL_1_RENDERSYSTEM_H

#include <memory>
#include <vector>
#include "Entity.h"
#include "Component.h"
#include "TextureManager.h"

class RenderSystem {
public:
    void render(std::vector<std::unique_ptr<Entity>> & entities) {
        for (auto& entity: entities) {
            if (entity->hasComponent<Transform>() && entity->hasComponent<Sprite>()) {
                auto& tr = entity->getComponent<Transform>();
                auto& sprite = entity->getComponent<Sprite>();

                sprite.dst.x = tr.position.x;
                sprite.dst.y = tr.position.y;

                // If the entity has an animation component, update the source rect
                if (entity->hasComponent<Animation>()) {
                    auto& anim = entity->getComponent<Animation>();
                    sprite.src = anim.clips[anim.currentClip].frameIndicies[anim.currentFrame];
                }

                TextureManager::draw(sprite.texture, sprite.src, sprite.dst);
            }
        }
    }
};

#endif //TUTORIAL_1_RENDERSYSTEM_H
