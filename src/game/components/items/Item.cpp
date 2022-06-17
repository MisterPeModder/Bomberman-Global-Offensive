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
#include "components/Scale.hpp"
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
    std::array<Item::Identifier, Item::ACTIVABLE_COUNT> Item::activables = {Item::Identifier::LandMine};

    std::array<Item, static_cast<size_t>(Item::Identifier::Count)> Item::items = {SpeedShoes(), FireUp(), BombUp(),
        KickShoes(), ChainBall(), FireDown(), BombDown(), InvertedControls(), LandMine()};

    bool Item::spawnRandomItem(ecs::SystemData data, raylib::core::Vector2u cell)
    {
        auto &randDevice = data.getResource<game::resources::RandomDevice>();

        /// Crate spawn an item ?
        if (randDevice.randInt(0, 99) >= 70)
            return false;

        /// Which item type ?
        int randVal = randDevice.randInt(0, 99);
        auto itemsPool((randVal < 65) ? std::span<Identifier, std::dynamic_extent>(powerUps)
                                      : ((randVal < 90) ? std::span<Identifier, std::dynamic_extent>(powerDowns)
                                                        : std::span<Identifier, std::dynamic_extent>(activables)));

        /// Which item ?
        randVal = randDevice.randInt(0, 99);
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
        auto &models = data.getResource<resources::Models>();
        raylib::model::Model *model;

        switch (identifier) {
            case Item::Identifier::SpeedShoes: model = &models.get("speed_up"); break;
            case Item::Identifier::FireUp: model = &models.get("range_up"); break;
            case Item::Identifier::FireDown: model = &models.get("range_down"); break;
            case Item::Identifier::BombUp: model = &models.get("C4_up"); break;
            case Item::Identifier::BombDown: model = &models.get("C4_down"); break;
            case Item::Identifier::KickShoes: model = &models.get("punch"); break;
            case Item::Identifier::ChainBall: model = &models.get("speed_down"); break;
            case Item::Identifier::InvertedControls: model = &models.get("speed_down"); break;
            default: model = &models.get("speed_up"); break; /// Avoid null pointers errors
        }

        data.getResource<ecs::Entities>()
            .builder()
            .with<ItemIdentifier>(data.getStorage<ItemIdentifier>(), identifier)
            .with<Position>(data.getStorage<Position>(), static_cast<float>(cell.x), 0.0f, static_cast<float>(cell.y))
            .with<Size>(data.getStorage<Size>(), 0.70f, 0.0f, 0.70f)
            .with<Scale>(data.getStorage<Scale>(), 1.f)
            .with<Destructible>(data.getStorage<Destructible>())
            .with<Color>(data.getStorage<Color>(), raylib::core::Color::WHITE)
            .with<ModelReference>(data.getStorage<ModelReference>(), *model)
            .build();

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
