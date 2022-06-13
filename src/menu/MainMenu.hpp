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
    };
} // namespace Menu

#endif /* !MAINMENU_HPP_ */