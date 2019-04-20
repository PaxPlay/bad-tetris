//
// Created by benedikt on 4/18/19.
//

#ifndef SDLTEST_MATRIX2D_H
#define SDLTEST_MATRIX2D_H

#include <cstdint>
#include <cstdlib>
#include <exception>
#include <stdexcept>

template <typename T>
class Matrix2D {
public:
    class Column {
    public:
        Column(T x, T y) : cell {x, y} {
        }

        T operator[](size_t index) const {
            if (index > 1) {
                throw std::out_of_range("Index is out of bounds for 2D vector.");
            }
            return cell[index];
        }
    private:
        T cell[2];
    };

    Matrix2D(T x1, T x2, T y1, T y2) : value { Column {x1, x2}, Column {y1, y2} } {
    }

    Column operator[](size_t index) const {
        if (index > 1) {
            throw std::out_of_range("Index is out of bounds for 2D vector.");
        }
        return value[index];
    }
private:
    Column value[2];
};

#endif //SDLTEST_MATRIX2D_H
