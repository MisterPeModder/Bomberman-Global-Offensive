/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Menu
*/

#pragma once

#include "ecs/Component.hpp"
#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/World.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Timer.hpp"
#include "raylib/textures/Image.hpp"

namespace Menu
{
    class MainMenu {
      public:
        MainMenu();
        ~MainMenu();
        /// Use it to run & display the main menu
        void run();
        struct Position : public ecs::Component {
            float x, y;

            Position(float px, float py) : x(px), y(py) {}
        };

      protected:
      private:
        ecs::World world;
        struct ButtonMenu : public ecs::System {};
    };
} // namespace Menu