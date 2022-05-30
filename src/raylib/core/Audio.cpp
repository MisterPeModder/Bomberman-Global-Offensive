/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Audio
*/

#include "Audio.hpp"

raylib::core::Audio::Audio()
{
}

raylib::core::Audio::Audio::~Audio()
{
}

namespace raylib {
    namespace core {
        Sound Audio::loadSound(const std::string fileName) { return LoadSound(fileName.c_str());}

        void Audio::unloadWave(Wave wave) {return UnloadWave(wave);}

        void Audio::setMasterVolume(float volume) {return setMasterVolume(volume);}

        bool Audio::isAudioDeviceReady(void) {return IsAudioDeviceReady();}

    }
}


