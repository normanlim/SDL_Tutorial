//
// Created by Norm on 9/23/2025.
//

#ifndef TUTORIAL_1_KEYBOARDINPUTSYSTEM_H
#define TUTORIAL_1_KEYBOARDINPUTSYSTEM_H
#include <SDL3/SDL_events.h>

#include "Component.h"

class KeyboardInputSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities, const SDL_Event& event) {

        for (auto& e : entities) {
            if (e->hasComponent<Velocity>()) {
                // should have 1 source of truth, only 1 file should handle all the movement, not multiple places
                auto& v = e->getComponent<Velocity>();
                if (event.type == SDL_EVENT_KEY_DOWN) {
                    switch (event.key.key) {
                        case SDLK_W:
                            v.direction.y = -1;
                            break;
                        case SDLK_S:
                            v.direction.y = 1;
                            break;
                        case SDLK_A:
                            v.direction.x = -1;
                            break;
                        case SDLK_D:
                            v.direction.x = 1;
                            break;
                        default:
                            break;
                    }
                }

                if (event.type == SDL_EVENT_KEY_UP) {
                    switch (event.key.key) {
                        case SDLK_W:
                            v.direction.y = 0;
                            break;
                        case SDLK_S:
                            v.direction.y = 0;
                            break;
                        case SDLK_A:
                            v.direction.x = 0;
                            break;
                        case SDLK_D:
                            v.direction.x = 0;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
};

#endif //TUTORIAL_1_KEYBOARDINPUTSYSTEM_H