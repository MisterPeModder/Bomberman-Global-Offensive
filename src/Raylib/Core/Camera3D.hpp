/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Camera3D
*/

#ifndef CAMERA3D_HPP_
#define CAMERA3D_HPP_

#include "Vector3.hpp"

extern "C"
{
#include <raylib.h>
}

namespace raylib
{

    namespace core
    {
        class Camera3D {
          public:
            /// @brief Default constructor
            explicit Camera3D();
            /// @brief Destructor
            ~Camera3D();
            /// @brief Deleted copy constructor
            explicit Camera3D(const Camera3D &) = delete;
            /// @brief Deleted copy operator
            Camera3D &operator=(const Camera3D &) = delete;
            /// @brief Move constructor
            /// @param camera The camera to move
            explicit Camera3D(Camera3D &&camera);
            /// @brief Move operator
            /// @param camera The camera to move
            /// @return the moved camera
            Camera3D &operator=(Camera3D &&camera);
            /// @brief Start 3D mode (BeginMode3D encapsulation)
            void begin3D();
            /// @brief End 3D mode (EndMode3D encapsulation)
            void end3D();
            /// @brief Get the position of the camera
            /// @return the position of the camera
            Vector3 getPosition() const;
            /// @brief Set the position of the camera
            /// @param position the new position of the camera
            void setPosition(Vector3 position);
            /// @brief Get the target of the camera
            /// @return the target of the camera
            Vector3 getTarget() const;
            /// @brief Set the target of the camera
            /// @param target the new target of the camera
            void setTarget(Vector3 target);
            /// @brief Get the 'up' of the camera
            /// @return the 'up' of the camera
            Vector3 getUp() const;
            /// @brief Set the 'up' of the camera
            /// @param up the new 'up' of the camera
            void setUp(Vector3 up);
            /// @brief Get the fovy of the camera
            /// @return the fovy of the camera
            float getFovy() const;
            /// @brief Set the fovy of the camera
            /// @param fovy the new fovy of the camera
            void setFovy(float fovy);
            /// @brief Get the projection of the camera
            /// @return the projection of the camera
            int getProjection() const;
            /// @brief Set the projection of the camera
            /// @param projection the new projection of the camera
            void setProjection(int projection);

          private:
            ::Camera3D _camera;
        };
    } // namespace core
} // namespace raylib

#endif /* CAMERA3D_HPP_ */
