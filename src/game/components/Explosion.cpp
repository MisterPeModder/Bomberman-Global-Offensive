/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Explosion
*/

#include "Explosion.hpp"
#include "Color.hpp"
#include "Model.hpp"
#include "Position.hpp"
#include "RotationAngle.hpp"
#include "RotationAxis.hpp"
#include "Size.hpp"
#include "ecs/Storage.hpp"
#include "game/resources/AssetMap.hpp"
#include "raylib/core/Color.hpp"

namespace game::components
{
    void Explosion::placeExplosion(ecs::SystemData data, raylib::core::Vector2u cell)
    {
        data.getResource<ecs::Entities>()
            .builder()
            .with<Explosion>(data.getStorage<Explosion>())
            .with<Position>(data.getStorage<Position>(), static_cast<float>(cell.x), 0.2f, static_cast<float>(cell.y))
            .with<ModelReference>(
                data.getStorage<ModelReference>(), data.getResource<resources::Models>().get("smoke_sphere"))
            .with<Size>(data.getStorage<Size>(), 0.2f, 0.2f, 0.2f)
            .with<RotationAngle>(data.getStorage<RotationAngle>(), 0.0f)
            .with<RotationAxis>(data.getStorage<RotationAxis>(), 0.f, 0.f, 0.f)
            .with<components::Color>(data.getStorage<components::Color>(), 160, 0, 0, 255)
            .build();
    }
} // namespace game::components
