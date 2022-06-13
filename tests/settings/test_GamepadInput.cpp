/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** test Gamepad Input
*/

#include "game/settings/GamepadInput.hpp"

#include <gtest/gtest.h>

using namespace game::settings;
using Gamepad = raylib::core::Gamepad;

TEST(GamepadInput, isButton)
{
    GamepadInput unknown;
    GamepadInput dpad(Gamepad::Button::DPAD_FACE_DOWN);
    GamepadInput axis(Gamepad::Axis::LEFT_X, GamepadInput::AxisDirection::Negative);

    EXPECT_FALSE(unknown.isButton());
    EXPECT_TRUE(dpad.isButton());
    EXPECT_FALSE(axis.isButton());
}
