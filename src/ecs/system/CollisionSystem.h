//
// Created by Norm on 10/3/2025.
//

#ifndef TUTORIAL_1_COLLISIONSYSTEM_H
#define TUTORIAL_1_COLLISIONSYSTEM_H
#include <memory>
#include <vector>

#include "Entity.h"


// Forward declaration to avoid circular dependency
class World;


class CollisionSystem {

public:
    void update(World& world);


private:
    std::vector<Entity*> queryCollidables(const std::vector<std::unique_ptr<Entity>>& entities);


};

#endif //TUTORIAL_1_COLLISIONSYSTEM_H