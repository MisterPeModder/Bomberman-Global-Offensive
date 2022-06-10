/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Menu
*/

#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

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
        /// Create all buttons needed in the manu
        void createsButtons(ecs::World &world);

      protected:
      private:
        ecs::World menu;
        struct ButtonMenu : public ecs::System {};
    };
} // namespace Menu

#endif /* !MAINMENU_HPP_ */