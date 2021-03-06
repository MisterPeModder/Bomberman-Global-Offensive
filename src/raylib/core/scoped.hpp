/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Scoped3D
*/

#ifndef RAYLIB_CORE_SCOPED3D_HPP_
#define RAYLIB_CORE_SCOPED3D_HPP_

#include "Audio.hpp"
#include "Camera2D.hpp"
#include "Camera3D.hpp"
#include "Window.hpp"
#include "raylib/shaders/Shader.hpp"
#include "raylib/textures/RenderTexture2D.hpp"

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
                inline Mode3D(const Camera3D &camera) { camera.begin3D(); };

                /// End the Mode3D
                inline ~Mode3D() { Camera3D::end3D(); };
            };

            /// Setup/End a 2D mode with a custom camera
            class Mode2D {
              public:
                /// Begin the Mode2D with the given camera.
                ///
                /// @param camera custom camera.
                inline Mode2D(const Camera2D &camera) { camera.begin2D(); };

                /// End the Mode2D
                inline ~Mode2D() { Camera2D::end2D(); };
            };

            /// Setup/End window drawing
            class Drawing {
              public:
                /// Begin the window drawing.
                inline Drawing() { Window::beginDrawing(); }

                /// End the window drawing.
                inline ~Drawing() { Window::endDrawing(); }
            };

            /// Setup/End audio device
            class AudioDevice {
              public:
                /// Begin the audio device.
                inline AudioDevice() { Audio::initDevice(); }

                /// End the audio device.
                inline ~AudioDevice() { Audio::closeDevice(); }
            };

            /// Setup/End shader mode
            class Shader {
              public:
                /// Begin the shader mode.
                inline Shader(const raylib::shaders::Shader &shader)
                {
                    raylib::shaders::Shader::beginShaderMode(shader);
                }

                /// End the shader mode.
                inline ~Shader() { raylib::shaders::Shader::endShaderMode(); }
            };

            /// Setup/End RenderTexture drawing
            class RenderTexture {
              public:
                /// Begin the RenderTexture drawing.
                inline RenderTexture(const raylib::textures::RenderTexture2D &texture)
                {
                    raylib::textures::RenderTexture2D::beginTextureMode(texture);
                }

                /// End the RenderTexture drawing.
                inline ~RenderTexture() { raylib::textures::RenderTexture2D::endTextureMode(); }
            };
        } // namespace scoped

    } // namespace core
} // namespace raylib

#endif /* !RAYLIB_CORE_SCOPED3D_HPP_ */
