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
        /// Base class for all widgets components
        class IWidgetComponent : public ecs::Component {
          public:
            /// Update the widget with the given action.
            ///
            /// @param self entity @a owning the component.
            /// @param ecs::SystemData view on the world.
            /// @param const Users::ActionEvent& informations about the action detected.
            /// @retval true if the action was consumed.
            /// @retval false if the action wasn't used.
            virtual bool update(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event) = 0;
        };
    } // namespace gui
} // namespace game

#endif /* !GAME_GUI_IWIDGETCOMPONENT_HPP_ */
