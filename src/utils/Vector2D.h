//
// Created by Norm on 9/23/2025.
//

#ifndef TUTORIAL_1_VECTOR2D_H
#define TUTORIAL_1_VECTOR2D_H

class Vector2D {
    public:
        float x = 0.0f;
        float y = 0.0f;

    Vector2D() {
        x = 0.0f;
        y = 0.0f;
    }

    Vector2D(float x, float y) : x(x), y(y) {}

    // Member operator function. Vector2D has to be on the left, float on the right to multiply.
    Vector2D operator*(float scaler) const;

    // Reverse, where Vector2D on left and float is on the left. We need to make this a non-member function
    // Friend makes it a non-member function.
    friend Vector2D operator*(float scaler, Vector2D& vec);


    // (member operator function) Vector that we want to return is on the left. Another vector is on the right.
    Vector2D& operator+=(const Vector2D& vec);


    Vector2D& normalize();

    //////// Assignment 4
    Vector2D& operator-=(const Vector2D& vec);

    Vector2D& operator/=(float scaler);

    Vector2D operator+(const Vector2D& vec) const;

    Vector2D operator-(const Vector2D &vec) const;

    bool operator==(const Vector2D &vec) const;

    bool operator!=(const Vector2D &vec) const;

    Vector2D operator-() const;
};

#endif //TUTORIAL_1_VECTOR2D_H