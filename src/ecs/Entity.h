//
// Created by Norm on 9/16/2025.
//

#ifndef TUTORIAL_1_ENTITY_H
#define TUTORIAL_1_ENTITY_H
#include "bitset"
#include "cstddef"
#include <array>
#include "ComponentType.h"
// Creates a const that is evaluated at compile time (constexpr), 32 components fits perfectly in a 32-bit integer.
constexpr std::size_t MAX_COMPONENTS = 32;

// bitset[0] = 1 , entity has component 0.
// Because bit operations are fast, and it works well for checking each frame.
using ComponentBitSet = std::bitset<MAX_COMPONENTS>;

// Fixed size array, where each index is a component.
// The index corresponds to the ComponentTypeID
// We use a fixed number of components, so that there is no dynamic allocation for the array. (Very efficient)
using ComponentArray = std::array<void*, MAX_COMPONENTS>;


class Entity {
    bool active = true; // important for cleanup later on

    ComponentArray componentArray{};
    ComponentBitSet componentBitSet{};

public:
    bool isActive() {
        return active;
    }

    void destroy() {
        active = false;
    }

    // Templates need to be implemented in header
    // USAGE? entity.hasComponent<Position>() -> returns true or false;
    template <typename T>
    bool hasComponent() {
        return componentBitSet[getComponentTypeID<T>()];
    }

    // Template that can receive multiple arguments
    // entity.addComponent<Position>(3,4)
    // entity.addComponent<Health>(100);
    template <typename T, typename... mArgs>
    T& addComponent(mArgs&&... args) {

        T* component(new T(std::forward<mArgs>(args)...));

        // Add the new component to the array
        componentArray[getComponentTypeID<T>()] = component;
        // Update the bitset to true
        componentBitSet[getComponentTypeID<T>()] = true;

        return *component;
    }

    // USAGE: entity.getComponent<Health>();
    template <typename T>
    T& getComponent() {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }

    template <typename T>
    void deactivateComponent() {
        componentBitSet[getComponentTypeID<T>()] = false;
    }

};

#endif //TUTORIAL_1_ENTITY_H
