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
        void Audio::initDevice(void) { InitAudioDevice(); }

        void Audio::closeDevice(void) { CloseAudioDevice(); }

        bool Audio::isDeviceReady() { return IsAudioDeviceReady(); }

        void Audio::setMasterVolume(float volume)
        {
            SetMasterVolume(volume);
            _volume = volume;
        }

        float Audio::getMasterVolume() { return _volume; }
    } // namespace core
} // namespace raylib
