/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** PlayerHud
*/

#include "PlayerHud.hpp"
#include <cmath>
#include "Color.hpp"
#include "Position.hpp"
#include "RotationAngle.hpp"
#include "Size.hpp"
#include "Texture2D.hpp"
#include "ecs/Storage.hpp"
#include "ecs/resource/Entities.hpp"
#include "game/resources/AssetMap.hpp"
#include "items/Item.hpp"
#include "raylib/core/Window.hpp"

namespace game::components
{
    static void buildItem(ecs::World::EntityBuilder &builder, raylib::core::Vector2f pos, raylib::core::Vector2f size,
        raylib::core::Vector2i orientation, raylib::core::Vector2f startPos, bool withText = false)
    {
        if (orientation.x < 0) {
            pos.x += std::fabs(size.x);
            if (withText)
                pos.x += 3;
        }
        builder.with<Position>(startPos.x + pos.x * orientation.x, startPos.y + pos.y, 0.f)
            .with<Size>(size.x, size.y, 0.f)
            .build();
    }

    void PlayerHud::createHud(User::UserId pOwner, raylib::textures::Texture2D &pHeadSkin, ecs::World &world)
    {
        auto &textures = world.getResource<game::resources::Textures>();
        size_t ownerId = static_cast<size_t>(pOwner);
        raylib::core::Vector2i orientation((ownerId % 2 == 0) ? 1 : -1, (ownerId / 2 == 0) ? 1 : -1);
        raylib::core::Vector2f start((ownerId % 2 == 0) ? 0 : 100, (ownerId / 2 == 0) ? 0 : 75);

        /// Player head
        buildItem(world.addEntity().with<Texture2DReference>(pHeadSkin).with<Color>(raylib::core::Color::WHITE),
            {0.f, 0.f}, {8.f * orientation.x, 15.f}, orientation, start);

        /// C4 count
        buildItem(
            world.addEntity().with<Texture2DReference>(textures.get("C4_up")).with<Color>(raylib::core::Color::WHITE),
            {10.f, 3.f}, {3.f, 5.3f}, orientation, start, true);

        /// Speed
        buildItem(world.addEntity()
                      .with<Texture2DReference>(textures.get("speed_up"))
                      .with<Color>(raylib::core::Color::WHITE),
            {18.f, 3.f}, {3.f, 5.3f}, orientation, start, true);

        /// Explosion range
        buildItem(world.addEntity()
                      .with<Texture2DReference>(textures.get("range_up"))
                      .with<Color>(raylib::core::Color::WHITE),
            {10.f, 10.f}, {3.f, 5.3f}, orientation, start, true);

        /// Activables
        size_t firstItem = static_cast<size_t>(Item::FIRST_ACTIVABLE);
        for (size_t i = firstItem; i < static_cast<size_t>(Item::Identifier::Count); i++) {
            buildItem(world.addEntity()
                          .with<Texture2DReference>(textures.get("mine"))
                          .with<Color>(raylib::core::Color::WHITE)
                          .with<RotationAngle>(-90),
                {2.f + 4 * (i - firstItem), 24.f}, {4.f, 7.1f}, orientation, start);
        }
    }
} // namespace game::components
