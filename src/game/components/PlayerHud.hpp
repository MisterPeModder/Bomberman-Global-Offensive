/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** PlayerHud
*/

#ifndef GAME_COMPONENTS_PLAYERHUD_HPP_
#define GAME_COMPONENTS_PLAYERHUD_HPP_

#include <string>
#include "User.hpp"
#include "ecs/Component.hpp"
#include "ecs/System.hpp"
#include "ecs/World.hpp"
#include "raylib/textures/Texture2D.hpp"

namespace game::components
{
    struct PlayerHud : public ecs::Component {
        User::UserId owner;

        PlayerHud(User::UserId pOwner) : owner(pOwner){};

        static void createHud(User::UserId pOwner, raylib::textures::Texture2D &pHeadSkin, ecs::World &world);
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_PLAYERHUD_HPP_ */
