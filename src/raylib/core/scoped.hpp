/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Scoped3D
*/

#ifndef RAYLIB_CORE_SCOPED3D_HPP_
#define RAYLIB_CORE_SCOPED3D_HPP_

#include "Camera3D.hpp"
#include "Window.hpp"

/// Raylib namespace
namespace raylib
{
    /// Core namespace (inside of raylib)
    namespace core
    {
        /// Use of RAII for the raylib Drawing related functions (with begin/end for each).
        namespace scoped
        {
            /// Setup/End a 3D mode with a custom camera
            class Mode3D {
              public:
                /// Begin the Mode3D with the given camera.
                ///
                /// @param camera custom camera.
                inline Mode3D(Camera3D &camera) { camera.begin3D(); };

                /// End the Mode3D
                inline ~Mode3D() { Camera3D::end3D(); };
            };

            /// Setup/End window drawing
            class Drawing {
              public:
                /// Begin the window drawing.
                inline Drawing() { Window::beginDrawing(); }

                /// End the window drawing.
                inline ~Drawing() { Window::endDrawing(); }
            };
        } // namespace scoped

    } // namespace core
} // namespace raylib

#endif /* !RAYLIB_CORE_SCOPED3D_HPP_ */
