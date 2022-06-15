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
#include "util/util.hpp"

namespace game::components
{
    std::vector<Item::Identifier> Item::powerUps = {Item::Identifier::SpeedShoes};
    std::vector<Item::Identifier> Item::powerDowns = {Item::Identifier::ChainBall};
    std::vector<Item::Identifier> Item::activables;

    std::vector<Item> Item::items = {SpeedShoes(), ChainBall()};

    bool Item::spawnRandomItem(ecs::SystemData data, raylib::core::Vector2u cell)
    {
        /// Crate spawn an item ?
        if (util::randInt(0, 99) >= 70)
            return false;

        /// Which type of item ? (To Do: handle Activables)
        int rand = util::randInt(0, 99);
        auto &itemsPool = (rand < 70) ? powerUps : powerDowns;

        /// Which item ?
        rand = util::randInt(0, 99);
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
        size_t id = static_cast<size_t>(identifier);

        data.getResource<ecs::Entities>()
            .builder()
            .with<ItemIdentifier>(data.getStorage<ItemIdentifier>(), identifier)
            .with<Position>(data.getStorage<Position>(), static_cast<float>(cell.x), 0.5f, static_cast<float>(cell.y))
            .with<Size>(data.getStorage<Size>(), 0.4f, 0.4f, 0.4f)
            .with<components::CubeColor>( /// Different color based on identifier waiting for models
                data.getStorage<CubeColor>(), raylib::core::Color(127 * (id % 3), 127 * (id / 3), 127 * (id / 9)))
            .with<components::Cube>(data.getStorage<Cube>())
            .build();
    }
} // namespace game::components
