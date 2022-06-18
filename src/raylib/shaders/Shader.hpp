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
        /// GLSL Shader class
        class Shader {
          public:
            /// Location of shader variable.
            using Location = int;
            /// Invalid variable location.
            static constexpr Location InvalidLocation = -1;

            /// Construct a new Shader.
            /// @note Not both files are required, it depends on the shaders needs.
            ///
            /// @param vertex vertex shader file (.vs).
            /// @param fragment fragment shader file (.fs)
            Shader(std::filesystem::path vertex, std::filesystem::path fragment = "");

            /// Destroy the shader.
            ~Shader();

            /// Begin a global shader drawing mode.
            ///
            /// @param shader shader to apply on drawed objects.
            static void beginShaderMode(const Shader &shader);

            /// End up a global shader drawing mode.
            static void endShaderMode();

            /// Get the Location of a variable.
            ///
            /// @param variable variable name.
            /// @param isUniform if it is a uniform or attribute variable.
            /// @return Location location of the variable. @ref InvalidLocation if not found.
            Location getLocation(std::string_view variable, bool isUniform = true) const;

            /// Set the Value of a variable.
            ///
            /// @param location location of the variable.
            /// @param value variable value.
            void setValue(Location location, float value) const;

            /// @copydoc raylib::shaders::Shader::setValue()
            void setValue(Location location, raylib::core::Vector2f value) const;

            /// @copydoc raylib::shaders::Shader::setValue()
            void setValue(Location location, raylib::core::Vector3f value) const;

            /// @copydoc raylib::shaders::Shader::setValue()
            void setValue(Location location, raylib::core::Vector4f value) const;

            /// @copydoc raylib::shaders::Shader::setValue()
            void setValue(Location location, int value) const;

            /// @copydoc raylib::shaders::Shader::setValue()
            void setValue(Location location, raylib::core::Vector2i value) const;

            /// @copydoc raylib::shaders::Shader::setValue()
            void setValue(Location location, raylib::core::Vector3i value) const;

            /// @copydoc raylib::shaders::Shader::setValue()
            void setValue(Location location, raylib::core::Vector4i value) const;

            /// @copydoc raylib::shaders::Shader::setValue()
            void setValue(Location location, const ::Matrix &mat) const;

            /// @copydoc raylib::shaders::Shader::setValue()
            void setValue(Location location, const raylib::textures::Texture2D &texture) const;

            /// Set a variable value by its name.
            ///
            /// @tparam T variable type
            /// @param name variable name
            /// @param value variable value.
            /// @param isUniform if it is a uniform or attribute variable.
            template <typename T> void setValue(std::string_view name, T value, bool isUniform = true) const
            {
                Location loc = getLocation(name, isUniform);

                if (loc == InvalidLocation)
                    return;
                setValue(loc, value);
            }

            /// Set multiple values for a unique variable (arrays).
            ///
            /// @param location Variable location.
            /// @param values array values.
            void setValues(Location location, std::span<float, std::dynamic_extent> values) const;

            /// @copydoc raylib::shaders::Shader::setValues()
            void setValues(Location location, std::span<raylib::core::Vector2f, std::dynamic_extent> values) const;

            /// @copydoc raylib::shaders::Shader::setValues()
            void setValues(Location location, std::span<raylib::core::Vector3f, std::dynamic_extent> values) const;

            /// @copydoc raylib::shaders::Shader::setValues()
            void setValues(Location location, std::span<raylib::core::Vector4f, std::dynamic_extent> values) const;

            /// @copydoc raylib::shaders::Shader::setValues()
            void setValues(Location location, std::span<int, std::dynamic_extent> values) const;

            /// @copydoc raylib::shaders::Shader::setValues()
            void setValues(Location location, std::span<raylib::core::Vector2i, std::dynamic_extent> values) const;

            /// @copydoc raylib::shaders::Shader::setValues()
            void setValues(Location location, std::span<raylib::core::Vector3i, std::dynamic_extent> values) const;

            /// @copydoc raylib::shaders::Shader::setValues()
            void setValues(Location location, std::span<raylib::core::Vector4i, std::dynamic_extent> values) const;

            /// Set multiple values for a unique variable (arrays) by its name.
            ///
            /// @tparam T variable type
            /// @param name variable name
            /// @param location Variable location.
            /// @param values array values.
            template <typename T>
            void setValues(std::string_view name, std::span<T, std::dynamic_extent> values, bool isUniform = true) const
            {
                Location loc = getLocation(name, isUniform);

                if (loc == InvalidLocation)
                    return;
                setValues(loc, values);
            }

            /// Bind the location of the variable name to the shader location @c location.
            /// @note Calling this is equivalent to 'asRaylib().locs[location] = getLocation(name)';
            ///
            /// @param location Index in the internal shader array (::Shader.locs).
            /// @param name variable name.
            /// @param isUniform if the variable is a uniform or attribute variable.
            void bindLocations(Location location, std::string_view name, bool isUniform = true);

            /// Fetches to path of a shader, based on the GLSL version.
            ///
            /// @param name The name of the shader.

            /// @returns The shader path.
            static std::filesystem::path getPath(std::string_view name);

            /// Get the raylib shader object.
            ///
            /// @return const ::Shader& shader.
            const ::Shader &asRaylib() const;

            /// Get the raylib shader object.
            ///
            /// @return ::Shader& shader.
            ::Shader &asRaylib();

          private:
            ::Shader _shader;
        };
    } // namespace shaders
} // namespace raylib

#endif /* !RAYLIB_SHADERS_SHADER_HPP_ */
