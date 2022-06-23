/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** PlayerHud
*/

#ifndef GAME_COMPONENTS_PLAYERHUD_HPP_
#define GAME_COMPONENTS_PLAYERHUD_HPP_

#include <array>
#include <string>
#include "Identity.hpp"
#include "Player.hpp"
#include "User.hpp"
#include "ecs/Component.hpp"
#include "ecs/System.hpp"
#include "ecs/World.hpp"
#include "raylib/core/Vector2.hpp"
#include "raylib/textures/Texture2D.hpp"

namespace game::components
{
    /// Player HUD Component
    struct PlayerHud : public ecs::Component {
      public:
        enum class Info {
            C4_Count,
            Range,
            Speed,
            SelectedItem,
            NoClip,
            LandMine,
            Stun,
            Smoke,
            Punch,
            Count,
        };
        /// User linked to the player.
        User::UserId owner;

        /// Construct a new Player Hud component.
        /// @warning Use the @ref createHud function to create all the HUD entities.
        ///
        /// @param pOwner owner of the player.
        PlayerHud(User::UserId pOwner) : owner(pOwner){};

        /// Create a player HUD.
        ///
        /// @param pOwner owner of the player.
        /// @param pHeadSkin player head texture.
        /// @param world world.
        static void createHud(User::UserId pOwner, raylib::textures::Texture2D &pHeadSkin, ecs::World &world);

        /// Update the displayed informations on the HUD.
        ///
        /// @param data world data.
        /// @param player player datas.
        void update(ecs::SystemData data, const Player &player);

      private:
        using InformationsArray = std::array<Identity::Id, static_cast<size_t>(Info::Count)>;

        /// Build the entities of the inventory section in the HUD.
        void buildInventory(ecs::World &world);

        /// Set the identifier of an HUD info.
        void setInfoId(Info info, Identity::Id id);

        /// Get the identifier of an HUD info.
        Identity::Id getInfoId(Info info) const;

        /// Get the position of an activable item selection.
        raylib::core::Vector2f getSelectionPosition(Item::Identifier id) const;

        InformationsArray _informations;
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_PLAYERHUD_HPP_ */
