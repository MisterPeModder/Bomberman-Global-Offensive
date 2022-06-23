
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Kick Shoes
*/

#include "Item.hpp"
#include "ecs/Storage.hpp"
#include "game/components/Color.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/Player.hpp"
#include "game/components/Position.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/Size.hpp"
#include "game/components/Texture2D.hpp"
#include "game/resources/AssetMap.hpp"

namespace game::components
{
    Item Item::KickShoes()
    {
        Item kickShoes;

        kickShoes.type = Item::Type::PowerUp;
        kickShoes.identifier = Item::Identifier::KickShoes;
        kickShoes.maxStack = 1;
        kickShoes.name = "Kick Shoes";
        kickShoes.duration = std::chrono::milliseconds::zero();
        kickShoes.dropRate = 10;
        /// Item is a passive, applied on collision with bombs
        kickShoes.onApply = [](ecs::Entity player, ecs::SystemData data) {
            auto &entities = data.getResource<ecs::Entities>();
            size_t owner = static_cast<size_t>(data.getStorage<Controlable>()[player.getId()].userId);

            /// Add the kick shoes icon in the player HUD.
            entities.builder()
                .with<Position>(
                    data.getStorage<Position>(), (owner % 2 == 0) ? 18.f : 76.f, (owner / 2 == 0) ? 15.f : 90.f)
                .with<Size>(data.getStorage<Size>(), 3.f, 5.3f)
                .with<Texture2DReference>(
                    data.getStorage<Texture2DReference>(), data.getResource<resources::Textures>().get("kick_shoes"))
                .with<RotationAngle>(data.getStorage<RotationAngle>(), -90)
                .with<Color>(data.getStorage<Color>(), raylib::core::Color::WHITE)
                .build();
            return true;
        };
        return kickShoes;
    }
} // namespace game::components
