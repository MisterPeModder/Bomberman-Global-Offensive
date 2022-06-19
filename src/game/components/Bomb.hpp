/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Bomb
*/

#ifndef GAME_COMPONENTS_BOMB_HPP_
#define GAME_COMPONENTS_BOMB_HPP_

#include <chrono>
#include "Identity.hpp"
#include "Position.hpp"
#include "ecs/Component.hpp"
#include "ecs/Entity.hpp"
#include "ecs/System.hpp"
#include "game/map/Map.hpp"
#include "raylib/core/Vector3.hpp"

namespace game::components
{
    /// Bomb component
    struct Bomb : public ecs::Component {
        /// Type of the bomb.
        enum class Type {
            Classic,
            LandMine,
        };
        /// Time when the bomb was placed
        std::chrono::milliseconds placedTime;
        /// Radius of the bomb explosion
        size_t radius;
        /// Delay before the explosion
        std::chrono::milliseconds explosionDelay;
        /// If the bomb has already exploded
        bool exploded;
        /// Id of the entity who placed the bomb.
        Identity::Id owner;
        /// @ref Type.
        Type type;

        /// Default bombs explosion delay
        static constexpr std::chrono::milliseconds DEFAULT_DELAY = std::chrono::milliseconds(2000);

        /// Construct a new Bomb component.
        ///
        /// @param pType bomb type.
        /// @param pOwner @ref owner.
        /// @param pRadius @ref radius
        /// @param pExplosionDelay @ref explosionDelay
        Bomb(std::chrono::milliseconds pPlacedTime, Type pType, Identity::Id pOwner, size_t pRadius = 1,
            std::chrono::milliseconds pExplosionDelay = DEFAULT_DELAY)
            : placedTime(pPlacedTime), radius(pRadius), explosionDelay(pExplosionDelay), exploded(false), owner(pOwner),
              type(pType){};

        /// Explode the bomb.
        ///
        /// @param pos position of the bomb.
        /// @param data world data.
        /// @param self entity @a owning of the bomb component.
        void explode(const Position &pos, ecs::SystemData data, ecs::Entity self);

        /// Change the bomb velocity.
        /// @warning Kill the entity @c self to create a new entity representing the new bomb (moving or not).
        /// @note If @c senderVelocity is null, the new Bomb will not have a Velocity component.
        ///
        /// @param data world data.
        /// @param self entity @a owning of the bomb component.
        /// @param senderVelocity sender velocity. (will become the kicked bomb velocity)
        void setVelocity(ecs::SystemData data, ecs::Entity self, raylib::core::Vector3f senderVelocity);

        /// Stop a kicked bomb.
        /// @warning Kill the entity @c self to create a new entity representing the new bomb.
        ///
        /// @param data world data.
        /// @param self entity @a owning of the bomb component.
        void stop(ecs::SystemData data, ecs::Entity self);

        /// Place a new bomb in the world.
        ///
        /// @param bombCell position of the bomb.
        /// @param data world data.
        /// @param bombType bomb type.
        /// @param owner entity @a owning the bomb component.
        /// @param range bomb range.
        /// @param delay bomb explosion delay.
        /// @param velocity velocity of the bomb (null for static bombs)
        /// @param avoidDuplicates Whether or not it must avoid multiple bombs on the same cell.
        /// @return true If the bomb was placed.
        /// @return false If the bomb couldn't be placed
        static bool placeBomb(raylib::core::Vector2u bombCell, ecs::SystemData data, Bomb::Type bombType,
            Identity::Id owner, size_t range, std::chrono::milliseconds delay = DEFAULT_DELAY,
            raylib::core::Vector3f velocity = {0.f, 0.f, 0.f}, bool avoidDuplicates = true);

      private:
        /// Limit above which an entity is considered on the cell (40% of its size overtaking on an adjacent cell)
        static constexpr float LivingEntityExplodeLimit = 0.4f;

        /// Test if at least @ref LivingEntityExplodeLimit % of a living entity size is on an adjacent exploded cell.
        ///
        /// @param pos entity position
        /// @param size entity size
        /// @param roundedPos2D entity main cell
        /// @param explodedPositions exploded positions
        /// @return true if the entity is on an adjacent exploded cell
        /// @return false if the entity isn't exploded on adjacent cells
        bool explodeLiving(raylib::core::Vector3f pos, raylib::core::Vector3f size, raylib::core::Vector2u roundedPos2D,
            const std::vector<raylib::core::Vector2u> &explodedPositions) const;

        /// Set the Bomb Model components
        ///
        /// @param builder bomb entity builder.
        /// @param data world data.
        /// @param type bomb type.
        /// @return ecs::Entities::Builder& bomb entity builder.
        static ecs::Entities::Builder &setBombModel(
            ecs::Entities::Builder &builder, ecs::SystemData data, Type type = Type::Classic);
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_BOMB_HPP_ */
