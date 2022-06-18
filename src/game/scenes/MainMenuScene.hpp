/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** MainMenuScene
*/

#ifndef GAME_SCENES_MAINMENUSCENES_HPP_
#define GAME_SCENES_MAINMENUSCENES_HPP_

#include "ecs/World.hpp"
#include "game/components/Identity.hpp"
#include "game/scenes/AScene.hpp"

namespace game
{
    class MainMenuScene : public AScene {
      public:
        enum WIDGET_ID {
            PLAY,
            OPTION,
            LOGOUT,
            JOIN_SLOT_ONE,
            JOIN_SLOT_TWO,
            JOIN_SLOT_THREE,
            JOIN_SLOT_FOUR,
        };
        MainMenuScene();

        void updateConnectedTexts();

        components::Identity::Id getFirstConnectedTextId() const;

      private:
        void loadPlayerSlot(size_t id);
        void loadPlayerInterface();

        components::Identity::Id _firstUserId;
    };
} // namespace game

#endif /* !GAME_SCENES_MAINMENUSCENES_HPP_ */
