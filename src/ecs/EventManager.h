//
// Created by Norm on 10/3/2025.
//

#ifndef TUTORIAL_1_EVENTMANAGER_H
#define TUTORIAL_1_EVENTMANAGER_H
#include <functional>
#include <vector>

#include "Entity.h"

struct CollisionEvent {
    Entity* entityA = nullptr;
    Entity* entityB = nullptr;
};


// Use the observer pattern
class EventManager {

public:

    // template<typename EventType>
    // void emit(const EventType& event) {
    //     // retrieve the list of subscripbers to certian events
    //     auto& listeners = getListeners<EventType>();
    //     // loop all the subscripbers to certian events
    //     for (auto& listener : listeners) {
    //         listener(event); // invoke the function here
    //     }
    // }
    //
    // template<typename EventType>
    // void subscribe(std::function<void(const EventType&)> callback) {
    //     // Pass in the callback / callable wrapper / subscription to the list of subscriptions
    //     getListeners<EventType>().push_back(callback);
    // }

    void emit(const CollisionEvent& event) const {
        for (const auto& listener: collisionListeners) {
            listener(event);
        }
    }
    void subscribe(std::function<void(const CollisionEvent&)> callback) {
        collisionListeners.emplace_back(std::move(callback));
    }

private:

    // Each event type essentially has its own std:vector of listeners without you having to manage it explicitly.
    // This is done using the static local.
    // std:function<void(const EventType&)> is the callable wrapper: can hold anything that can be called like a function. (lambda, free function, functor, etc.)

    // template<typename EventType>
    // std::vector<std::function<void(const EventType&)>>& getListeners() {
    //     static std::vector<std::function<void(const EventType&)>> listeners;
    //     return listeners;
    // }

    std::vector<std::function<void(const CollisionEvent&)>> collisionListeners;



};

#endif //TUTORIAL_1_EVENTMANAGER_H