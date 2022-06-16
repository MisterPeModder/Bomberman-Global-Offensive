/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Console
*/

#include "Console.hpp"
#include "util/util.hpp"

namespace game ::gui
{
    Console::Console()
        : font(util::makePath("assets", "fonts", "Inconsolata", "Inconsolata-Regular.ttf"), 20, nullptr, 0), timer(0.0)
    {
    }
} // namespace game::gui
