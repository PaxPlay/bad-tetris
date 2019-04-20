//
// Created by benedikt on 4/18/19.
//

#ifndef SDLTEST_VECTOR2D_H
#define SDLTEST_VECTOR2D_H

#include "Matrix2D.h"

template <typename T>
class Vector2D {
public:
    Vector2D() : x({}), y({}) {
    }

    Vector2D(T x, T y) : x(x), y(y){
    }

    Vector2D(const Vector2D& vec) : x(vec.x), y(vec.y) {
    }

    Vector2D operator*(const Matrix2D<T>& matrix) const {
        return Vector2D(
                x * matrix[0][0] + y * matrix[1][0],
                x * matrix[0][1] + y * matrix[1][1]);
    }

    Vector2D operator+(const Vector2D<T>& vec) const {
        return Vector2D(
                x + vec.x,
                y + vec.y);
    }

    union {
        struct {
            T x, y;
        };
        T fields[2];
    };
};


#endif //SDLTEST_VECTOR2D_H
