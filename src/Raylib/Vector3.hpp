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
        /// @brief 3D constructor of the vector
        /// @param x the X axis value of the vector
        /// @param y the Y axis value of the vector
        /// @param z the Z axis value of the vector
        Vector3(float x, float y, float z);
        /// @brief 2D constructor of the vector (defaults Z to 0)
        /// @param x the X axis value of the vector
        /// @param y the Y axis value of the vector
        Vector3(float x, float y);
        /// @brief 1D constructor of the vector (defaults Y and Z to 0)
        /// @param x the X axis value of the vector
        Vector3(float x);
        /// @brief Default constructor of the vector (defaults all values to 0)
        Vector3();
        /// @brief The copy constructor
        /// @param vector the vector to copy
        Vector3(const Vector3& vector);
        /// @brief Destructor
        ~Vector3();
        /// @brief Get the X axis value of the vector
        /// @return the X axis value of the vector
        float getX() const { return _x; }
        /// @brief Set the X acis value of the vector
        /// @param x the new X axis value of the vector
        void setX(float x) { _x = x; }
        /// @brief Get the Y axis value of the vector
        /// @return the Y axis value of the vector
        float getY() const { return _y; }
        /// @brief Set the Y acis value of the vector
        /// @param y the new Y axis value of the vector
        void setY(float y) { _y = y; }
        /// @brief Get the Z axis value of the vector
        /// @return the Z axis value of the vector
        float getZ() const { return _z; }
        /// @brief Set the Z acis value of the vector
        /// @param z the new Z axis value of the vector
        void setZ(float z) { _z = z; }
        /// @brief The Vector3 copy operator
        /// @param vector the Vector3 to copy
        Vector3 &operator=(const Vector3& vector);
        /// @brief The Vector3 add operator
        /// @param vector the Vector3 to add
        Vector3 operator+(const Vector3& vector);
        /// @brief The Vector3 assignment add operator
        /// @param vector the Vector3 to assignment add
        Vector3 &operator+=(const Vector3& vector);
        /// @brief The Vector3 remove operator
        /// @param vector the Vector3 to remove
        Vector3 operator-(const Vector3& vector);
        /// @brief The Vector3 assignment remove operator
        /// @param vector the Vector3 to assignment remove
        Vector3 &operator-=(const Vector3& vector);
        /// @brief The Vector3 multiply operator
        /// @param vector the Vector3 to multiply
        Vector3 operator*(const Vector3& vector);
        /// @brief The Vector3 assignment multiply operator
        /// @param vector the Vector3 to assignment multiply
        Vector3 &operator*=(const Vector3& vector);
        /// @brief The Vector3 divide operator
        /// @param vector the Vector3 to divide
        Vector3 operator/(const Vector3& vector);
        /// @brief The Vector3 assignment divide operator
        /// @param vector the Vector3 to assignment divide
        Vector3 &operator/=(const Vector3& vector);

    private:
        float _x;
        float _y;
        float _z;
};

}

#endif /* VECTOR3_HPP_ */
