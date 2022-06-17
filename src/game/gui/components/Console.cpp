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
    Console::Console() : font(util::makePath("assets", "fonts", "Inconsolata-Medium.ttf"), 20, nullptr, 65535) {}
} // namespace game::gui
