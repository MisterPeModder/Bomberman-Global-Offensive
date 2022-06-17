/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Console
*/

#ifndef GAME_GUI_COMPONENTS_CONSOLE_HPP_
#define GAME_GUI_COMPONENTS_CONSOLE_HPP_

#include "ecs/Component.hpp"
#include "ecs/Entity.hpp"
#include "ecs/System.hpp"
#include "game/Users.hpp"
#include "raylib/text/Font.hpp"

namespace game ::gui
{
    struct Console : public ecs::Component {
        raylib::text::Font font;

        Console();

        static bool handleInput(ecs::Entity self, ecs::SystemData data, game::Users::ActionEvent const &event);
    };
} // namespace game::gui

#endif // !defined(GAME_GUI_COMPONENTS_CONSOLE_HPP_)
