/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Console
*/

#ifndef GAME_GUI_COMPONENTS_CONSOLE_HPP_
#define GAME_GUI_COMPONENTS_CONSOLE_HPP_

#include "ecs/Component.hpp"
#include "raylib/text/Font.hpp"

namespace game ::gui
{
    struct Console : public ecs::Component {
        raylib::text::Font font;
        double timer;

        Console();
    };
} // namespace game::gui

#endif // !defined(GAME_GUI_COMPONENTS_CONSOLE_HPP_)
