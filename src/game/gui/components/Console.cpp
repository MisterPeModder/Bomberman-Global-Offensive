/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Console
*/

#include "Console.hpp"
#include "ecs/Storage.hpp"
#include "game/components/KeyboardInput.hpp"
#include "logger/Logger.hpp"
#include "util/util.hpp"

#include "script/Engine.hpp"
#include "script/JsException.hpp"

#include "ecs/Storage.hpp"
#include "ecs/System.hpp"

#include <algorithm>
#include <string>

namespace game::gui
{
    Console::Console()
        : font(util::makePath("assets", "fonts", "Inconsolata-Medium.ttf"), 20, nullptr, 65535),
          logger(std::cout, "console"), output(), outputSeverity(Logger::Severity::Information)
    {
    }

    void Console::setOutput(Logger::Severity severity, std::string &&newOutput)
    {
        this->logger.log(severity, newOutput);
        this->output = std::move(newOutput);
        this->outputSeverity = severity;
    }

    bool Console::runCommand(ecs::Entity self, ecs::SystemData data, std::string_view toRun)
    {
        auto engine = bmjs::Engine::instance().lock();
        Console &console = data.getStorage<Console>()[self.getId()];

        if (!engine) {
            console.setOutput(Logger::Severity::Error, "Failed to run console input");
            return true;
        }
        try {
            std::string result(engine->loadString(toRun));
            console.setOutput(Logger::Severity::Information, std::move(result));
        } catch (bmjs::JsException const &error) {
            console.setOutput(Logger::Severity::Error, error.what());
        }
        return true;
    }

    bool Console::handleInput(ecs::Entity self, ecs::SystemData data, game::Users::ActionEvent const &event)
    {
        if (event.action == GameAction::TOGGLE_CONSOLE && event.value > 0.f) {
            game::KeyboardInput &input = data.getStorage<game::KeyboardInput>()[self.getId()];
            input.focused = !input.focused;
            return true;
        }
        return false;
    }
} // namespace game::gui
