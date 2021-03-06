/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Shader
*/

#include "Shader.hpp"
#include "raylib/textures/Texture2D.hpp"
#include "util/util.hpp"

namespace raylib
{
    namespace shaders
    {
        Shader::Shader(std::filesystem::path vertex, std::filesystem::path fragments)
        {
            _shader = LoadShader((vertex.empty()) ? nullptr : vertex.generic_string().c_str(),
                (fragments.empty()) ? nullptr : fragments.generic_string().c_str());
        }

        Shader::~Shader() { UnloadShader(_shader); }

        void Shader::beginShaderMode(const Shader &shader) { BeginShaderMode(shader._shader); }
        void Shader::endShaderMode() { EndShaderMode(); }

        Shader::Location Shader::getLocation(std::string_view variable, bool isUniform) const
        {
            return (isUniform) ? GetShaderLocation(_shader, variable.data())
                               : GetShaderLocationAttrib(_shader, variable.data());
        }

        void Shader::setValue(Location location, float value) const
        {
            SetShaderValue(_shader, location, &value, SHADER_UNIFORM_FLOAT);
        }

        void Shader::setValue(Location location, raylib::core::Vector2f value) const
        {
            SetShaderValue(_shader, location, &value, SHADER_UNIFORM_VEC2);
        }

        void Shader::setValue(Location location, raylib::core::Vector3f value) const
        {
            SetShaderValue(_shader, location, &value, SHADER_UNIFORM_VEC3);
        }

        void Shader::setValue(Location location, raylib::core::Vector4f value) const
        {
            SetShaderValue(_shader, location, &value, SHADER_UNIFORM_VEC4);
        }

        void Shader::setValue(Location location, int value) const
        {
            SetShaderValue(_shader, location, &value, SHADER_UNIFORM_INT);
        }

        void Shader::setValue(Location location, raylib::core::Vector2i value) const
        {
            SetShaderValue(_shader, location, &value, SHADER_UNIFORM_IVEC2);
        }

        void Shader::setValue(Location location, raylib::core::Vector3i value) const
        {
            SetShaderValue(_shader, location, &value, SHADER_UNIFORM_IVEC3);
        }

        void Shader::setValue(Location location, raylib::core::Vector4i value) const
        {
            SetShaderValue(_shader, location, &value, SHADER_UNIFORM_IVEC4);
        }

        void Shader::setValue(Location location, const ::Matrix &mat) const
        {
            SetShaderValueMatrix(_shader, location, mat);
        }

        void Shader::setValue(Location location, const raylib::textures::Texture2D &texture) const
        {
            SetShaderValueTexture(_shader, location, texture.asRaylib());
        }

        void Shader::setValues(Location location, std::span<float, std::dynamic_extent> values) const
        {
            SetShaderValueV(_shader, location, values.data(), SHADER_UNIFORM_FLOAT, values.size());
        }

        void Shader::setValues(Location location, std::span<raylib::core::Vector2f, std::dynamic_extent> values) const
        {
            SetShaderValueV(_shader, location, values.data(), SHADER_UNIFORM_VEC2, values.size());
        }

        void Shader::setValues(Location location, std::span<raylib::core::Vector3f, std::dynamic_extent> values) const
        {
            SetShaderValueV(_shader, location, values.data(), SHADER_UNIFORM_VEC3, values.size());
        }

        void Shader::setValues(Location location, std::span<raylib::core::Vector4f, std::dynamic_extent> values) const
        {
            SetShaderValueV(_shader, location, values.data(), SHADER_UNIFORM_VEC4, values.size());
        }

        void Shader::setValues(Location location, std::span<int, std::dynamic_extent> values) const
        {
            SetShaderValueV(_shader, location, values.data(), SHADER_UNIFORM_INT, values.size());
        }

        void Shader::setValues(Location location, std::span<raylib::core::Vector2i, std::dynamic_extent> values) const
        {
            SetShaderValueV(_shader, location, values.data(), SHADER_UNIFORM_IVEC2, values.size());
        }

        void Shader::setValues(Location location, std::span<raylib::core::Vector3i, std::dynamic_extent> values) const
        {
            SetShaderValueV(_shader, location, values.data(), SHADER_UNIFORM_IVEC3, values.size());
        }

        void Shader::setValues(Location location, std::span<raylib::core::Vector4i, std::dynamic_extent> values) const
        {
            SetShaderValueV(_shader, location, values.data(), SHADER_UNIFORM_IVEC4, values.size());
        }

        void Shader::bindLocations(Location location, std::string_view name, bool isUniform)
        {
            Location loc = getLocation(name, isUniform);

            if (loc == InvalidLocation)
                return;
            _shader.locs[location] = loc;
        }

        std::filesystem::path Shader::getPath(std::string_view name)
        {
#ifdef PLATFORM_DESKTOP
            return util::makePath("assets", "shaders", "glsl330", name);
#else // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
            return util::makePath("assets", "shaders", "glsl100", name);
#endif
        }

        const ::Shader &Shader::asRaylib() const { return _shader; }

        ::Shader &Shader::asRaylib() { return _shader; }

    } // namespace shaders
} // namespace raylib
