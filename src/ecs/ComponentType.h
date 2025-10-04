//
// Created by Norm on 9/16/2025.
//

#ifndef TUTORIAL_1_COMPONENTTYPE_H
#define TUTORIAL_1_COMPONENTTYPE_H
#include "cstddef"

// Creating a type alias for std::size_t;
// size_t is designed to represent sizes and indicies because its unsigned and its very large (long, long)
using ComponentTypeID = std::size_t;


// free function, not inside a class. When defined in a header file, each .cpp file that includes this header (ComponentType.h)
// Would get its own definition causing a linker error, and using inline merges them into one definition.
// This is a global counter generator function, returns a unique number everytime we call it.
// Making ID static, means it will keep its value through multiple calls of this function.
inline ComponentTypeID getComponentTypeID() {
    static ComponentTypeID id = 0;
    return id++;
}

// Template allows us to use generic types. An overloaded function of above.
// We can overload this function because they have different signatures.
// Template is inline by default.
// getComponentTypeID<Position>() --> would always return 0
// getComponentTypeID<Health>() --> would always return 1
// a static local variable is created and initialized once
template <typename T>
ComponentTypeID getComponentTypeID() {
    static ComponentTypeID typeID = getComponentTypeID();
    return typeID;
}

#endif //TUTORIAL_1_COMPONENTTYPE_H
