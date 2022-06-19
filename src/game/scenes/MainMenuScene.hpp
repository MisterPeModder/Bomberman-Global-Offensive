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

#include <queue>

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

        void updateConnectedTexts();

      private:
        enum PLAYER_TEXTURE {
          TERRORIST_1,
          TERRORIST_2,
          COUNTER_TERRORIST_1,
          COUNTER_TERRORIST_2,
          NO_SENSE,
          RAINBOW,
          NONE
        };

        localization::ResourceString playerTextureToRessourceString(PLAYER_TEXTURE texture);
        void loadPlayerSlot(size_t id);
        void loadPlayerInterface();
        void loadLeftButtons();

        components::Identity::Id _firstUserId;
        std::queue<PLAYER_TEXTURE> _playerTextures;
    };
} // namespace game

#endif /* !GAME_SCENES_MAINMENUSCENES_HPP_ */
