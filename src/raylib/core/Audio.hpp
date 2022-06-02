/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Audio
*/

#ifndef RAYLIB_CORE_AUDIO_HPP_
#define RAYLIB_CORE_AUDIO_HPP_

#include <raylib.h>

namespace raylib
{
    namespace core {
        class Audio {
            public:
                Audio();
                ~Audio();
                static void initAudioDevice(void);
                static void closeAudioDevice(void);
                static bool isAudioDeviceReady(void);
                static void setMasterVolume(float volume);
            protected:
            private:
        };
    }
}

#endif /*RAYLIB_CORE_AUDIO_HPP_*/