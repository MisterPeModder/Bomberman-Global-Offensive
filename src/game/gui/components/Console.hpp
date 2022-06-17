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
#include "ecs/system/SystemData.hpp"

#include "game/Users.hpp"
#include "logger/Logger.hpp"
#include "raylib/text/Font.hpp"

#include <string>

namespace game
{
    struct KeyboardInput;
}

namespace game::gui
{
    struct Console : public ecs::Component {
        raylib::text::Font font;

        /// The output line
        std::string output;
        /// The log level of the output line.
        Logger::Severity outputSeverity;

        Console();

        /// Changes the active output.
        void setOutput(Logger::Severity severity, std::string &&newOutput);

        /// @param self the entity id of the input.
        /// @param data the system data.
        /// @param toRun the contents of the input field.
        ///
        /// @returns whether the input field should be cleared.
        static bool runCommand(ecs::Entity self, ecs::SystemData data, std::string_view toRun);

        /// @param self the entity id of the input.
        /// @param data the system data.
        /// @param event The action event.
        ///
        /// @returns whether the input field should be cleared.
        static bool handleInput(ecs::Entity self, ecs::SystemData data, game::Users::ActionEvent const &event);
    };
} // namespace game::gui

#endif // !defined(GAME_GUI_COMPONENTS_CONSOLE_HPP_)
