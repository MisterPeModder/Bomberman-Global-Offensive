/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Item
*/

#include "Item.hpp"
#include <span>
#include <stdexcept>
#include "ItemIdentifier.hpp"

#include "components/Color.hpp"
#include "components/Cube.hpp"
#include "components/CubeColor.hpp"
#include "components/Model.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"

#include "ecs/Storage.hpp"
#include "ecs/resource/Entities.hpp"

#include "game/components/Destructible.hpp"
#include "game/components/Model.hpp"

#include "game/resources/AssetMap.hpp"
#include "game/resources/RandomDevice.hpp"

namespace game::components
{
    std::array<Item::Identifier, Item::POWER_UP_COUNT> Item::powerUps = {
        Item::Identifier::SpeedShoes, Item::Identifier::FireUp, Item::Identifier::BombUp, Item::Identifier::KickShoes};
    std::array<Item::Identifier, Item::POWER_DOWN_COUNT> Item::powerDowns = {Item::Identifier::ChainBall,
        Item::Identifier::FireDown, Item::Identifier::BombDown, Item::Identifier::InvertedControls};
    std::array<Item::Identifier, Item::ACTIVABLE_COUNT> Item::activables;

    std::array<Item, static_cast<size_t>(Item::Identifier::Count)> Item::items = {
        SpeedShoes(), FireUp(), BombUp(), KickShoes(), ChainBall(), FireDown(), BombDown(), InvertedControls()};

    bool Item::spawnRandomItem(ecs::SystemData data, raylib::core::Vector2u cell)
    {
        auto &randDevice = data.getResource<game::resources::RandomDevice>();

        /// Crate spawn an item ?
        if (randDevice.randInt(0, 99) >= 70)
            return false;

        /// Which item type ? (To do: Activable type)
        auto itemsPool((randDevice.randInt(0, 99) < 70) ? std::span<Identifier, std::dynamic_extent>(powerUps)
                                                        : std::span<Identifier, std::dynamic_extent>(powerDowns));

        /// Which item ?
        int randVal = randDevice.randInt(0, 99);
        size_t i = 0;
        int current = getItem(itemsPool[i]).dropRate;

        while (randVal >= current) {
            ++i;
            if (i >= itemsPool.size())
                throw std::logic_error("Invalid drop rates.");
            current += getItem(itemsPool[i]).dropRate;
        }
        spawnItem(itemsPool[i], data, cell);
        return true;
    }

    const Item &Item::getItem(Identifier identifier) { return items[static_cast<size_t>(identifier)]; }

    void Item::spawnItem(Identifier identifier, ecs::SystemData data, raylib::core::Vector2u cell)
    {
        //size_t id = static_cast<size_t>(identifier);

        auto &item = data.getResource<ecs::Entities>()
                        .builder()
                        .with<ItemIdentifier>(data.getStorage<ItemIdentifier>(), identifier)
                        .with<Position>(
                            data.getStorage<Position>(), static_cast<float>(cell.x), 0.5f, static_cast<float>(cell.y))
                        .with<Size>(data.getStorage<Size>(), 0.4f, 0.4f, 0.4f)
                        .with<Destructible>(data.getStorage<Destructible>())
                        .with<Color>(data.getStorage<Color>(), raylib::core::Color::WHITE);
        switch (identifier) {
            case Item::Identifier::SpeedShoes:
                (void)item.with<ModelReference>(data.getStorage<ModelReference>(),
                    data.getResource<resources::Models>().get("speed_up"));
                break;

            case Item::Identifier::FireUp:
                (void)item.with<ModelReference>(data.getStorage<ModelReference>(),
                    data.getResource<resources::Models>().get("range_up"));
                break;

            case Item::Identifier::FireDown:
                (void)item.with<ModelReference>(data.getStorage<ModelReference>(),
                    data.getResource<resources::Models>().get("range_down"));
                break;

            case Item::Identifier::BombUp:
                (void)item.with<ModelReference>(data.getStorage<ModelReference>(),
                    data.getResource<resources::Models>().get("C4_up"));
                break;

            case Item::Identifier::BombDown:
                (void)item.with<ModelReference>(data.getStorage<ModelReference>(),
                    data.getResource<resources::Models>().get("C4_down"));
                break;

            case Item::Identifier::KickShoes:
                (void)item.with<ModelReference>(data.getStorage<ModelReference>(),
                    data.getResource<resources::Models>().get("punch"));
                break;

            case Item::Identifier::ChainBall:
                (void)item.with<ModelReference>(data.getStorage<ModelReference>(),
                    data.getResource<resources::Models>().get("speed_down"));
                break;

            case Item::Identifier::InvertedControls:
                (void)item.with<ModelReference>(data.getStorage<ModelReference>(),
                    data.getResource<resources::Models>().get("speed_down"));
                break;
            default: break;
        }
        item.build();
        // SpeedShoes,
        // FireUp,
        // BombUp,
        // KickShoes,
        // /// Power Down
        // ChainBall,
        // FireDown,
        // BombDown,
        // InvertedControls,
        // Count,
    }
} // namespace game::components
