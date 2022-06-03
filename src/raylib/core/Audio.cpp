/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Audio
*/

#include "Audio.hpp"

namespace raylib
{
    namespace core
    {
        void Audio::initAudioDevice(void) { InitAudioDevice(); }

        void Audio::closeAudioDevice(void) { CloseAudioDevice(); }

        bool Audio::isAudioDeviceReady() { return IsAudioDeviceReady(); }

        void Audio::setMasterVolume(float volume) { SetMasterVolume(volume); }
    } // namespace core
} // namespace raylib
