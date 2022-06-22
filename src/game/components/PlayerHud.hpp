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
        User::UserId owner;

        PlayerHud(User::UserId pOwner) : owner(pOwner){};

        static void createHud(User::UserId pOwner, raylib::textures::Texture2D &pHeadSkin, ecs::World &world);

        void update(ecs::SystemData data, const Player &player);

      private:
        using InformationsArray = std::array<Identity::Id, static_cast<size_t>(Info::Count)>;

        void buildInventory(ecs::World &world);
        void setInfoId(Info info, Identity::Id id);
        Identity::Id getInfoId(Info info) const;
        raylib::core::Vector2f getSelectionPosition(Item::Identifier id) const;

        InformationsArray _informations;
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_PLAYERHUD_HPP_ */
