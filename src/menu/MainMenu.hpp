/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Menu
*/

#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

#include "ecs/Storage.hpp"
#include "ecs/World.hpp"
#include "game/resources/Map.hpp"
#include "raylib/core/Camera3D.hpp"

namespace Menu
{
    class MainMenu {
      public:
        MainMenu(ecs::World &world);
        ~MainMenu();
        void setup(raylib::core::Camera3D &camera, size_t width, size_t depth);
        /// Create all buttons needed in the manu
        void createsButtons();
        void modulePlayerFirst();
        void modulePlayerSecond();
        void modulePlayerThird();
        void modulePlayerFourth();
        void drawFrame(const raylib::core::Camera3D &camera);

      protected:
      private:
        ecs::World &_world;
    };
} // namespace Menu

#endif /* !MAINMENU_HPP_ */