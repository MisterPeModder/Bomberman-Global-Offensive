/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Shader
*/

#ifndef RAYLIB_SHADERS_SHADER_HPP_
#define RAYLIB_SHADERS_SHADER_HPP_

#include <filesystem>
#include <span>
#include "raylib/core/Vector2.hpp"
#include "raylib/core/Vector3.hpp"

extern "C"
{
#include <raylib.h>
}

namespace raylib
{
    namespace textures
    {
        class Texture2D;
    }

    namespace shaders
    {
        class Shader {
          public:
            using Location = int;

            Shader(std::filesystem::path vertex, std::filesystem::path fragments);
            ~Shader();

            Location getUniformLocation(std::string_view uniform) const;
            Location getAttributeLocation(std::string_view attribute) const;

            void setValue(Location location, float value);
            void setValue(Location location, raylib::core::Vector2f value);
            void setValue(Location location, raylib::core::Vector3f value);
            // void setValue(Location location, raylib::core::Vector4f value);
            void setValue(Location location, int value);
            void setValue(Location location, raylib::core::Vector2i value);
            void setValue(Location location, raylib::core::Vector3i value);
            // void setValue(Location location, raylib::core::Vector4i value);

            void setValue(Location location, const ::Matrix &mat);
            void setValue(Location location, const raylib::textures::Texture2D &texture);

            void setValues(Location location, std::span<float, std::dynamic_extent> values);
            void setValues(Location location, std::span<raylib::core::Vector2f, std::dynamic_extent> values);
            void setValues(Location location, std::span<raylib::core::Vector3f, std::dynamic_extent> values);
            // void setValues(Location location, std::span<raylib::core::Vector4f, std::dynamic_extent> values);
            void setValues(Location location, std::span<int, std::dynamic_extent> values);
            void setValues(Location location, std::span<raylib::core::Vector2i, std::dynamic_extent> values);
            void setValues(Location location, std::span<raylib::core::Vector3i, std::dynamic_extent> values);
            // void setValues(Location location, std::span<raylib::core::Vector4i, std::dynamic_extent> values);

          private:
            ::Shader _shader;
        };
    } // namespace shaders
} // namespace raylib

//  RLAPI int GetShaderLocation(Shader shader, const char *uniformName);       // Get shader uniform location
// RLAPI int GetShaderLocationAttrib(Shader shader, const char *attribName);  // Get shader attribute
// location
// RLAPI void SetShaderValue(Shader shader, int locIndex, const void *value, int uniformType);
// Set shader uniform value
// RLAPI void SetShaderValueV(Shader shader, int locIndex, const void *value, int uniformType,
// int count);   // Set shader uniform value vector
// RLAPI void SetShaderValueMatrix(Shader shader, int locIndex, Matrix
// mat);         // Set shader uniform value (matrix 4x4)
// RLAPI void SetShaderValueTexture(Shader shader, int locIndex,
// Texture2D texture); // Set shader uniform value for texture (sampler2d)

// RLAPI void UnloadShader(Shader shader); //
// Unload shader from GPU memory (VRAM)

#endif /* !RAYLIB_SHADERS_SHADER_HPP_ */
