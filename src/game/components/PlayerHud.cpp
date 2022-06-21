/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** PlayerHud
*/

#include "PlayerHud.hpp"
#include "Color.hpp"
#include "Position.hpp"
#include "Size.hpp"
#include "Texture2D.hpp"
#include "ecs/Storage.hpp"
#include "ecs/resource/Entities.hpp"
#include "raylib/core/Window.hpp"

namespace game::components
{
    void PlayerHud::createHud(User::UserId pOwner, raylib::textures::Texture2D &pHeadSkin, ecs::World &world)
    {
        size_t ownerId = static_cast<size_t>(pOwner);
        raylib::core::Vector2i orientation((ownerId % 2 == 0) ? 1 : -1, (ownerId / 2 == 0) ? 1 : -1);
        raylib::core::Vector2f start((ownerId % 2 == 0) ? 0 : 92, (ownerId / 2 == 0) ? 0 : 75);

        world.addEntity()
            .with<Position>(start.x, start.y, 0.f)
            .with<Texture2DReference>(pHeadSkin)
            .with<Size>(8.f * orientation.x, 15.f)
            .with<Color>(raylib::core::Color::WHITE)
            .build();
    }
} // namespace game::components
