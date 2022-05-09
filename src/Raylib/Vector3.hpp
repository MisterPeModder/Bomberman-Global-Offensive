/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Vector3
*/

#pragma once

namespace raylib {

class Vector3 {
    public:
        Vector3(float x, float y, float z) : _x(x), _y(y), _z(z) {}
        Vector3(float x, float y) : _x(x), _y(y), _z(0.f) {}
        ~Vector3() {}
        float getX() const { return _x; }
        float getY() const { return _y; }
        float getZ() const { return _z; }

    protected:
    private:
        float _x;
        float _y;
        float _z;
};

}
