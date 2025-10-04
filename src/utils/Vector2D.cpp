//
// Created by Norm on 9/23/2025.
//

#include "Vector2D.h"

#include <math.h>


// Member operator function so we can use the Vector2D on the left hand side.
Vector2D Vector2D::operator*(float scaler) const {
    return Vector2D(x * scaler, y * scaler);
}


// Non-member operator function so we make sure use of putting the Vector2D on the right hand side
Vector2D operator*(float scaler, Vector2D& vec) {
    return Vector2D(vec.x * scaler, vec.y * scaler);
}

// Member operator function so we can use the Vector2D that we want to change on the left-hand-side.
Vector2D& Vector2D::operator+=(const Vector2D& vec) {
    this->x += vec.x;
    this->y += vec.y;

    return *this; // return a dereferenced pointer so we don't return another copy
}

Vector2D &Vector2D::normalize() {
    float length = sqrt(x*x + y*y); // sqrt(x^2 + y^2), Pythagorean theorem.

    // length cannot be zero, have to prevent divide by 0 error.
    // if length was 4.4, x=x/4.4 , y=y/4.4;
    if (length > 0 ) {
        this->x /= length;
        this->y /= length;
    }

    return *this;
}

////// Assignment 4

// Member operator function for subtraction
Vector2D& Vector2D::operator-=(const Vector2D& vec) {
    this->x -= vec.x;
    this->y -= vec.y;

    return *this; // return a dereferenced pointer so we don't return another copy
}

// Member operator function for division
Vector2D& Vector2D::operator/=(float scaler) {
    // Prevent divide by zero
    if (scaler != 0.0f) {
        this->x /= scaler;
        this->y /= scaler;
    }
    return *this;
}

// Member operator function for addition
Vector2D Vector2D::operator+(const Vector2D& vec) const {
    return Vector2D(this->x + vec.x, this->y + vec.y);
}

// Member operator function for subtraction
Vector2D Vector2D::operator-(const Vector2D& vec) const {
    return Vector2D(this->x - vec.x, this->y - vec.y);
}

// Member operator function for equality comparison
bool Vector2D::operator==(const Vector2D& vec) const {
    return (this->x == vec.x && this->y == vec.y);
}

// Member operator function for inequality comparison
bool Vector2D::operator!=(const Vector2D& vec) const {
    return !(*this == vec); // Reuse the == operator
}

// Unary negation operator (flips the direction of the vector)
Vector2D Vector2D::operator-() const {
    return Vector2D(-this->x, -this->y);
}
