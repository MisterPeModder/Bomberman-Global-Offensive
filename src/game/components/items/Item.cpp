/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Item
*/

#include "Item.hpp"
#include <stdexcept>
#include "ItemIdentifier.hpp"
#include "components/Cube.hpp"
#include "components/CubeColor.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "ecs/Storage.hpp"
#include "ecs/resource/Entities.hpp"
#include "game/resources/RandomDevice.hpp"
#include "util/util.hpp"

namespace game::components
{
    std::array<Item::Identifier, Item::POWER_UP_COUNT> Item::powerUps = {Item::Identifier::SpeedShoes};
    std::array<Item::Identifier, Item::POWER_DOWN_COUNT> Item::powerDowns;
    std::array<Item::Identifier, Item::ACTIVABLE_COUNT> Item::activables;

    std::array<Item, static_cast<size_t>(Item::Identifier::Count)> Item::items = {SpeedShoes()};

    bool Item::spawnRandomItem(ecs::SystemData data, raylib::core::Vector2u cell)
    {
        auto &randDevice = data.getResource<game::resources::RandomDevice>();

        if (randDevice.randInt(0, 99) >= 70)
            return false;
        /// To Do: handle item types
        auto &itemsPool = powerUps;

        int rand = randDevice.randInt(0, 99);
        size_t i = 0;
        int current = getItem(itemsPool[i]).dropRate;

        while (rand >= current) {
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
        data.getResource<ecs::Entities>()
            .builder()
            .with<ItemIdentifier>(data.getStorage<ItemIdentifier>(), identifier)
            .with<Position>(data.getStorage<Position>(), static_cast<float>(cell.x), 0.5f, static_cast<float>(cell.y))
            .with<Size>(data.getStorage<Size>(), 0.4f, 0.4f, 0.4f)
            .with<components::CubeColor>(data.getStorage<CubeColor>(), raylib::core::Color::YELLOW)
            .with<components::Cube>(data.getStorage<Cube>())
            .build();
    }
} // namespace game::components
