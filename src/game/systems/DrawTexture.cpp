/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** DrawTexture
*/

#include "DrawTexture.hpp"
#include <cmath>
#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "game/components/Color.hpp"
#include "game/components/Position.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"
#include "game/components/Scale.hpp"
#include "game/components/Size.hpp"
#include "game/components/Texture2D.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/textures/Texture2D.hpp"

namespace game::systems
{
    void DrawTexture::run(ecs::SystemData data)
    {
        auto &textures = data.getStorage<game::components::Texture2D>();
        auto &poses = data.getStorage<game::components::Position>();
        auto &scales = data.getStorage<game::components::Scale>();
        auto &colors = data.getStorage<game::components::Color>();
        auto &rotations = data.getStorage<game::components::RotationAngle>();

        for (auto [texture, rotation, pos, scale, color] : ecs::join(textures, rotations, poses, scales, colors)) {
            texture.draw(
                {pos.x / 100 * raylib::core::Window::getWidth(), pos.y / 100 * raylib::core::Window::getHeight()},
                rotation.rotationAngle, scale.scale, color);
        }
    }

    void DrawFlippedTexture::run(ecs::SystemData data)
    {
        auto &textures = data.getStorage<game::components::Texture2DReference>();
        auto &poses = data.getStorage<game::components::Position>();
        auto &sizes = data.getStorage<game::components::Size>();
        auto &colors = data.getStorage<game::components::Color>();
        auto maybeRotation = ecs::maybe(data.getStorage<game::components::RotationAngle>());
        Vector2 origin = {0.0f, 0.0f};

        for (auto [textureRef, pos, size, color, angle] : ecs::join(textures, poses, sizes, colors, maybeRotation)) {
            raylib::core::Vector2f scale(
                raylib::core::Window::getWidth() / 100.f, raylib::core::Window::getHeight() / 100.f);

            auto &raylibTex = textureRef.object.asRaylib();
            Rectangle source = {0.f, 0.f, static_cast<float>(raylibTex.width * std::copysign(1, size.x)),
                static_cast<float>(raylibTex.height * std::copysign(1, size.y))};
            Rectangle dest = {
                scale.x * pos.x, scale.y * pos.y, std::fabs(size.x) * scale.x, std::fabs(size.y) * scale.y};

            DrawTexturePro(raylibTex, source, dest, origin, (angle) ? angle->rotationAngle : 0, color.asRaylib());
        }
    }
} // namespace game::systems
