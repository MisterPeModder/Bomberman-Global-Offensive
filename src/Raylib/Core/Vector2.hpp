/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Vector2
*/

#ifndef VECTOR2_HPP_
#define VECTOR2_HPP_

namespace raylib {

namespace Core {

class Vector2 {
    public:
        /// @brief Constructor of the vector
        /// @param x the X axis value of the vector
        /// @param y the Y axis value of the vector
        Vector2(float x = 0.f, float y = 0.f);
        /// @brief The copy constructor
        /// @param vector the vector to copy
        Vector2(const Vector2& vector);
        /// @brief Destructor
        ~Vector2();
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
        /// @brief The Vector2 copy operator
        /// @param vector the Vector2 to copy
        Vector2 &operator=(const Vector2& vector);
        /// @brief The Vector2 add operator
        /// @param vector the Vector2 to add
        Vector2 operator+(const Vector2& vector);
        /// @brief The Vector2 assignment add operator
        /// @param vector the Vector2 to assignment add
        Vector2 &operator+=(const Vector2& vector);
        /// @brief The Vector2 remove operator
        /// @param vector the Vector2 to remove
        Vector2 operator-(const Vector2& vector);
        /// @brief The Vector2 assignment remove operator
        /// @param vector the Vector2 to assignment remove
        Vector2 &operator-=(const Vector2& vector);
        /// @brief The Vector2 multiply operator
        /// @param vector the Vector2 to multiply
        Vector2 operator*(const Vector2& vector);
        /// @brief The Vector2 assignment multiply operator
        /// @param vector the Vector2 to assignment multiply
        Vector2 &operator*=(const Vector2& vector);
        /// @brief The Vector2 divide operator
        /// @param vector the Vector2 to divide
        Vector2 operator/(const Vector2& vector);
        /// @brief The Vector2 assignment divide operator
        /// @param vector the Vector2 to assignment divide
        Vector2 &operator/=(const Vector2& vector);

    private:
        float _x;
        float _y;
};

}

}

#endif /* VECTOR2_HPP_ */
