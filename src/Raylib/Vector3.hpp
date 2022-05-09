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
        void setX(float x) { _x = x; }
        float getY() const { return _y; }
        void setY(float y) { _y = y; }
        float getZ() const { return _z; }
        void setZ(float z) { _z = z; }

    protected:
    private:
        float _x;
        float _y;
        float _z;
};

}
