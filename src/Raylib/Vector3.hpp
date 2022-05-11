/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Vector3
*/

#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

namespace raylib {

class Vector3 {
    public:
        Vector3(float x, float y, float z);
        Vector3(float x, float y);
        ~Vector3();
        float getX() const { return _x; }
        void setX(float x) { _x = x; }
        float getY() const { return _y; }
        void setY(float y) { _y = y; }
        float getZ() const { return _z; }
        void setZ(float z) { _z = z; }
        Vector3 &operator=(const Vector3& vector);
        Vector3(const Vector3& vector);

    private:
        float _x;
        float _y;
        float _z;
};

}

#endif /* VECTOR3_HPP_ */
