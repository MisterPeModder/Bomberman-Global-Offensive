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
#include "Rectangle.hpp"
#include "RotationAngle.hpp"
#include "Size.hpp"
#include "Textual.hpp"
#include "Texture2D.hpp"
#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Entities.hpp"
#include "game/resources/AssetMap.hpp"
#include "items/Item.hpp"
#include "logger/Logger.hpp"
#include "raylib/core/Window.hpp"

namespace game::components
{
    static ecs::Entity buildItem(ecs::World::EntityBuilder &builder, raylib::core::Vector2f pos,
        raylib::core::Vector2f size, raylib::core::Vector2i orientation, raylib::core::Vector2f startPos,
        float rightOffset = 0.f)
    {
        if (orientation.x < 0) {
            pos.x += std::fabs(size.x);
            pos.x += rightOffset;
        }
        return builder.with<Position>(startPos.x + pos.x * orientation.x, startPos.y + pos.y, 0.f)
            .with<Size>(size.x, size.y, 0.f)
            .build();
    }

    raylib::core::Vector2f PlayerHud::getSelectionPosition(Item::Identifier id) const
    {
        return {((static_cast<size_t>(owner) % 2 == 0) ? 1.f : 78.5f)
                + (static_cast<size_t>(id) - static_cast<size_t>(Item::FIRST_ACTIVABLE)) * 4.f,
            (static_cast<size_t>(owner) / 2 == 0) ? 15.6f : 91.f};
    }

    void PlayerHud::buildInventory(ecs::World &world)
    {
        auto &textures = world.getResource<game::resources::Textures>();
        auto &identities = world.getStorage<Identity>();
        raylib::core::Vector2f pos = getSelectionPosition(Item::Identifier::NoClip);

        /// Activables Outline
        world.addEntity()
            .with<Position>(pos.x, pos.y)
            .with<Size>(20.5f, 9.f)
            .with<Rectangle>(2.f, raylib::core::Color::BLACK)
            .with<Color>(raylib::core::Color::BROWN)
            .build();
        /// Activable selection
        setInfoId(Info::SelectedItem,
            identities[world.addEntity()
                           .with<Position>(pos.x, pos.y)
                           .with<Size>(4.f, 9.f)
                           .with<Rectangle>(2.f, raylib::core::Color::BLUE)
                           .with<Color>(raylib::core::Color::BLANK)
                           .with<Identity>()
                           .build()
                           .getId()]
                .id);

        /// Activables
        size_t firstItem = static_cast<size_t>(Item::FIRST_ACTIVABLE);
        size_t nbItems = static_cast<size_t>(Item::Identifier::Count) - firstItem;
        for (size_t i = 0; i < nbItems; i++) {
            raylib::textures::Texture2D *texture = nullptr;
            switch (static_cast<Item::Identifier>(i + static_cast<size_t>(Item::FIRST_ACTIVABLE))) {
                case Item::Identifier::NoClip: texture = &textures.get("no_clip"); break;
                case Item::Identifier::LandMine: texture = &textures.get("mine"); break;
                case Item::Identifier::StunGrenade: texture = &textures.get("stun"); break;
                case Item::Identifier::SmokeGrenade: texture = &textures.get("smoke"); break;
                case Item::Identifier::Punch: texture = &textures.get("punch"); break;
                default: &textures.get("no_clip"); break;
            }

            world.addEntity()
                .with<Position>(pos.x + 4 * i, pos.y + 8.5f)
                .with<Size>(4.f, 7.1f)
                .with<Texture2DReference>(*texture)
                .with<Color>(raylib::core::Color::WHITE)
                .with<RotationAngle>(-90)
                .build();

            setInfoId(static_cast<Info>(static_cast<size_t>(Info::NoClip) + i),
                identities[world.addEntity()
                               .with<Position>(pos.x + 3.5f + 4 * i, pos.y + 0.4f)
                               .with<Textual>("0", 20, raylib::core::Color::RED)
                               .with<Identity>()
                               .build()
                               .getId()]
                    .id);
        }
    }

    void PlayerHud::createHud(User::UserId pOwner, raylib::textures::Texture2D &pHeadSkin, ecs::World &world)
    {
        auto &textures = world.getResource<game::resources::Textures>();
        size_t ownerId = static_cast<size_t>(pOwner);
        raylib::core::Vector2i orientation((ownerId % 2 == 0) ? 1 : -1, (ownerId / 2 == 0) ? 1 : -1);
        raylib::core::Vector2f start((ownerId % 2 == 0) ? 0 : 100, (ownerId / 2 == 0) ? 0 : 75);
        auto &identities = world.getStorage<Identity>();
        auto &playerHud = world.getStorage<PlayerHud>()[world.addEntity().with<PlayerHud>(pOwner).build().getId()];

        buildItem(world.addEntity()
                      .with<Rectangle>(2.f, raylib::core::Color::BLACK)
                      .with<Color>(raylib::core::Color(180, 180, 180, 180)),
            {0.f, 0.f}, {25.f, 25.f}, orientation, start);

        /// Player head
        buildItem(world.addEntity().with<Texture2DReference>(pHeadSkin).with<Color>(raylib::core::Color::WHITE),
            {0.f, 0.f}, {8.f * orientation.x, 15.f}, orientation, start);

        /// C4 count
        buildItem(
            world.addEntity().with<Texture2DReference>(textures.get("C4_up")).with<Color>(raylib::core::Color::WHITE),
            {10.f, 3.f}, {3.f, 5.3f}, orientation, start, 3.f);
        playerHud.setInfoId(Info::C4_Count,
            identities[buildItem(
                           world.addEntity().with<Textual>("1/1", 25, raylib::core::Color::BLACK).with<Identity>(),
                           {14.f, 4.f}, {0.f, 0.f}, orientation, start, -2.f)
                           .getId()]
                .id);

        /// Speed
        buildItem(world.addEntity()
                      .with<Texture2DReference>(textures.get("speed_up"))
                      .with<Color>(raylib::core::Color::WHITE),
            {18.f, 3.f}, {3.f, 5.3f}, orientation, start, 3.f);
        playerHud.setInfoId(Info::Speed,
            identities[buildItem(
                           world.addEntity().with<Textual>("4.0", 25, raylib::core::Color::BLACK).with<Identity>(),
                           {22.f, 4.f}, {0.f, 0.f}, orientation, start, -2.f)
                           .getId()]
                .id);

        /// Explosion range
        buildItem(world.addEntity()
                      .with<Texture2DReference>(textures.get("range_up"))
                      .with<Color>(raylib::core::Color::WHITE),
            {10.f, 10.f}, {3.f, 5.3f}, orientation, start, 3.f);
        playerHud.setInfoId(Info::Range,
            identities[buildItem(world.addEntity().with<Textual>("1", 25, raylib::core::Color::BLACK).with<Identity>(),
                           {14.f, 11.f}, {0.f, 0.f}, orientation, start, -2.f)
                           .getId()]
                .id);

        playerHud.buildInventory(world);
    }

    void PlayerHud::setInfoId(Info info, Identity::Id id) { _informations[static_cast<size_t>(info)] = id; }
    Identity::Id PlayerHud::getInfoId(Info info) const { return _informations[static_cast<size_t>(info)]; }

    void PlayerHud::update(ecs::SystemData data, const Player &player)
    {
        for (auto [text, id] : ecs::join(data.getStorage<Textual>(), data.getStorage<Identity>())) {
            if (id.id == getInfoId(Info::C4_Count)) {
                size_t bombs = player.stats.bombLimit;
                text.text = std::to_string(bombs - player.placedBombs) + "/" + std::to_string(bombs);
            } else if (id.id == getInfoId(Info::Speed))
                text.text = std::to_string(player.stats.speed).substr(0, 3);
            else if (id.id == getInfoId(Info::Range))
                text.text = std::to_string(player.stats.bombRange);
            else {
                size_t firstItem = static_cast<size_t>(Item::FIRST_ACTIVABLE);
                for (size_t i = firstItem; i < static_cast<size_t>(Item::Identifier::Count); i++)
                    if (id.id == getInfoId(static_cast<Info>(static_cast<size_t>(Info::NoClip) + i - firstItem))) {
                        size_t count = player.inventory[static_cast<Item::Identifier>(i)];
                        text.text = std::to_string(count);
                        text.color = (count > 0) ? raylib::core::Color::GREEN : raylib::core::Color::RED;
                    }
            }
        }

        for (auto [pos, id] : ecs::join(data.getStorage<Position>(), data.getStorage<Identity>())) {
            if (id.id == getInfoId(Info::SelectedItem))
                pos = getSelectionPosition(player.inventory.selected);
        }
    }
} // namespace game::components
