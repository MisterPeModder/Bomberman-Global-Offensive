/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Audio
*/

#include "Audio.hpp"

namespace raylib {
    namespace core {
        Audio::Audio()
        {
        }
        Audio::~Audio()
        {
        }
        void Audio::initAudioDevice(void) {return InitAudioDevice();}

        void Audio::closeAudioDevice(void) {return CloseAudioDevice();}
    }
}
