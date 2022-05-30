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

        void Audio::unloadWave(Wave wave) {UnloadWave(wave);}

        void Audio::setMasterVolume(float volume) {setMasterVolume(volume);}

        bool Audio::isAudioDeviceReady(void) {return IsAudioDeviceReady();}

        void Audio::closeAudioDevice(void) {CloseAudioDevice();}

        void Audio::initAudioDevice(void) {initAudioDevice();}

    }
}


