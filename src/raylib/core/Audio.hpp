/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Audio
*/

#ifndef RAYLIB_CORE_AUDIO_HPP_
#define RAYLIB_CORE_AUDIO_HPP_

#include <raylib.h>
#include <string>

namespace raylib
{
    namespace core {
        class Audio {
            public:
                Audio();
                ~Audio();
                //masterisation of music
                Sound loadSound(const std::string fileName);
                void unloadWave(Wave wave);
                void setMasterVolume(float volume);
                bool isAudioDeviceReady(void);
                void closeAudioDevice(void);
                void initAudioDevice(void);
                void playSound(Sound sound);
                void stopSound(Sound sound);
                void pauseSound(Sound sound);
                //void resumeSound(Sound sound);
                bool isSoundPlaying(Sound sound);
                void setSoundVolume(Sound sound, float volume);

            protected:
            private:
                ::Sound _sound;
        };
    }
}

#endif /*RAYLIB_CORE_AUDIO_HPP_*/