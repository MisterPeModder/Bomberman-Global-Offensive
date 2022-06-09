/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** IWidgetComponent
*/

#ifndef GAME_GUI_IWIDGETCOMPONENT_HPP_
#define GAME_GUI_IWIDGETCOMPONENT_HPP_

#include "ecs/Component.hpp"
#include "ecs/Entity.hpp"
#include "ecs/System.hpp"
#include "game/Users.hpp"


namespace game
{
    namespace gui
    {
        class IWidgetComponent : public ecs::Component {
          public:
            virtual bool update(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event) = 0;
        };
    } // namespace gui
} // namespace game

#endif /* !GAME_GUI_IWIDGETCOMPONENT_HPP_ */
