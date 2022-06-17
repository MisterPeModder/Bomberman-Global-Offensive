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
#include "raylib/core/Vector4.hpp"

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
            static constexpr Location InvalidLocation = -1;

            Shader(std::filesystem::path vertex, std::filesystem::path fragment = "");
            ~Shader();

            static void beginShaderMode(const Shader &shader);
            static void endShaderMode();

            Location getLocation(std::string_view variable, bool isUniform = true) const;

            void setValue(Location location, float value) const;
            void setValue(Location location, raylib::core::Vector2f value) const;
            void setValue(Location location, raylib::core::Vector3f value) const;
            void setValue(Location location, raylib::core::Vector4f value) const;
            void setValue(Location location, int value) const;
            void setValue(Location location, raylib::core::Vector2i value) const;
            void setValue(Location location, raylib::core::Vector3i value) const;
            void setValue(Location location, raylib::core::Vector4i value) const;
            void setValue(Location location, const ::Matrix &mat) const;
            void setValue(Location location, const raylib::textures::Texture2D &texture) const;

            template <typename T> void setValue(std::string_view name, T value, bool isUniform = true) const
            {
                Location loc = getLocation(name);

                if (loc == InvalidLocation)
                    return;
                setValue(loc, value);
            }

            void setValues(Location location, std::span<float, std::dynamic_extent> values) const;
            void setValues(Location location, std::span<raylib::core::Vector2f, std::dynamic_extent> values) const;
            void setValues(Location location, std::span<raylib::core::Vector3f, std::dynamic_extent> values) const;
            void setValues(Location location, std::span<raylib::core::Vector4f, std::dynamic_extent> values) const;
            void setValues(Location location, std::span<int, std::dynamic_extent> values) const;
            void setValues(Location location, std::span<raylib::core::Vector2i, std::dynamic_extent> values) const;
            void setValues(Location location, std::span<raylib::core::Vector3i, std::dynamic_extent> values) const;
            void setValues(Location location, std::span<raylib::core::Vector4i, std::dynamic_extent> values) const;

            template <typename T>
            void setValues(std::string_view name, std::span<T, std::dynamic_extent> values, bool isUniform = true) const
            {
                Location loc = getLocation(name);

                if (loc == InvalidLocation)
                    return;
                setValues(loc, values);
            }

            void bindLocations(Location location, std::string_view name, bool isUniform = true);

            const ::Shader &asRaylib() const;
            ::Shader &asRaylib();

          private:
            ::Shader _shader;
        };
    } // namespace shaders
} // namespace raylib

#endif /* !RAYLIB_SHADERS_SHADER_HPP_ */
