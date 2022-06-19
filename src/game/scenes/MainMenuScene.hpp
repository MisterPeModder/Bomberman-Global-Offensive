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

#include "localization/Resources.hpp"

#include <deque>

namespace game
{
    class MainMenuScene : public AScene {
      public:
        enum WIDGET_ID {
            PLAY,
            SETTINGS,
            LOGOUT,
            JOIN_SLOT_ONE,
            JOIN_SLOT_TWO,
            JOIN_SLOT_THREE,
            JOIN_SLOT_FOUR,
        };
        MainMenuScene();

        void setupWorld() override;

        void loadPlayerTextures();
        void updateConnectedTexts();
        void updateSkins();

        User::USER_SKINS getUnusedSkin();

      private:
        void loadPlayerSlot(size_t id);
        void loadPlayerInterface();
        void loadLeftButtons();

        components::Identity::Id _models[4];
        components::Identity::Id _animations[4];
        components::Identity::Id _connectedTexts[4];
        components::Identity::Id _skinTexts[4];
        std::deque<User::USER_SKINS> _availableSkins;
    };
} // namespace game

#endif /* !GAME_SCENES_MAINMENUSCENES_HPP_ */
