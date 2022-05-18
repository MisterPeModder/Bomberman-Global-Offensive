/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Camera3D
*/

#ifndef RAYLIB_CORE_CAMERA3D_HPP_
#define RAYLIB_CORE_CAMERA3D_HPP_

#include "Vector3.hpp"

extern "C"
{
#include <raylib.h>
}

/// Raylib namespace
namespace raylib
{
    /// Core namespace (inside of raylib)
    namespace core
    {
        /// The Camera3D class that encapsulates the raylib 3D camera
        class Camera3D {
            public:
                /// Default constructor
                explicit Camera3D();

                /// Destructor
                ~Camera3D();

                /// Deleted copy constructor
                explicit Camera3D(const Camera3D &) = delete;

                /// Deleted copy operator
                Camera3D &operator=(const Camera3D &) = delete;

                /// Move constructor
                ///
                /// @param camera The camera to move
                explicit Camera3D(Camera3D &&camera);

                /// Move operator
                ///
                /// @param camera The camera to move
                ///
                /// @return the moved camera
                Camera3D &operator=(Camera3D &&camera);

                /// Start 3D mode (BeginMode3D encapsulation)
                void begin3D();

                /// End 3D mode (EndMode3D encapsulation)
                void end3D();

                /// Get the position of the camera
                ///
                /// @return the position of the camera
                Vector3 getPosition() const;

                /// Set the position of the camera
                ///
                /// @param position the new position of the camera
                void setPosition(Vector3 position);

                /// Get the target of the camera
                ///
                /// @return the target of the camera
                Vector3 getTarget() const;

                /// Set the target of the camera
                ///
                /// @param target the new target of the camera
                void setTarget(Vector3 target);

                /// Get the 'up' of the camera
                ///
                /// @return the 'up' of the camera
                Vector3 getUp() const;

                /// Set the 'up' of the camera
                ///
                /// @param up the new 'up' of the camera
                void setUp(Vector3 up);

                /// Get the fovY of the camera
                ///
                /// @return the fovY of the camera
                float getFovY() const;

                /// Set the fovY of the camera
                ///
                /// @param fovY the new fovY of the camera
                void setFovY(float fovY);

                /// Get the projection of the camera
                ///
                /// @return the projection of the camera
                int getProjection() const;

                /// Set the projection of the camera
                ///
                /// @param projection the new projection of the camera
                void setProjection(int projection);

            private:
                ::Camera3D _camera;
        };
    } // namespace core
} // namespace raylib

#endif /* RAYLIB_CORE_CAMERA3D_HPP_ */
