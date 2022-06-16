/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Camera2D
*/

#ifndef RAYLIB_CORE_CAMERA2D_HPP_
#define RAYLIB_CORE_CAMERA2D_HPP_

#include "Vector2.hpp"

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
        /// The Camera2D class that encapsulates the raylib 2D camera
        class Camera2D {
          public:
            /// Encapsulation of the CameraMode enum
            enum CameraMode {
                CUSTOM = CAMERA_CUSTOM,
                FREE = CAMERA_FREE,
                ORBITAL = CAMERA_ORBITAL,
                FIRST_PERSON = CAMERA_FIRST_PERSON,
                THIRD_PERSON = CAMERA_THIRD_PERSON
            };

            /// Default constructor
            explicit Camera2D();

            /// Destructor
            ~Camera2D();

            /// Deleted copy constructor
            explicit Camera2D(const Camera2D &) = delete;

            /// Deleted copy operator
            Camera2D &operator=(const Camera2D &) = delete;

            /// Move constructor
            ///
            /// @param camera The camera to move
            explicit Camera2D(Camera2D &&camera);

            /// Move operator
            ///
            /// @param camera The camera to move
            ///
            /// @return the moved camera
            Camera2D &operator=(Camera2D &&camera);

            /// Start 2D mode (BeginMode2D encapsulation)
            void begin2D() const;

            /// End 2D mode (EndMode2D encapsulation)
            static void end2D();

            /// Get the offset of the camera
            ///
            /// @return the offset of the camera
            Vector2f getOffset() const;

            /// Set the offset of the camera
            ///
            /// @param offset the new offset of the camera
            void setOffset(Vector2f offset);

            /// Get the target of the camera
            ///
            /// @return the target of the camera
            Vector2f getTarget() const;

            /// Set the target of the camera
            ///
            /// @param target the new target of the camera
            void setTarget(Vector2f target);

            /// Get the rotation of the camera
            ///
            /// @return the rotation of the camera
            float getRotation() const;

            /// Set the rotation of the camera
            ///
            /// @param rotation the new rotation of the camera
            void setRotation(float rotation);

            /// Get the zoom of the camera
            ///
            /// @return the zoom of the camera
            float getZoom() const;

            /// Set the zoom of the camera
            ///
            /// @param zoom the new zoom of the camera
            void setZoom(float zoom);

          private:
            ::Camera2D _camera;
        };
    } // namespace core
} // namespace raylib

#endif /* RAYLIB_CORE_CAMERA2D_HPP_ */
