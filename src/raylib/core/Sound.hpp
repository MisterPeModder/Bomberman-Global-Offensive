/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Music
*/

#ifndef RAYLIB_CORE_MUSIC_HPP_
#define RAYLIB_CORE_MUSIC_HPP_

extern "C" 
{
#include <raylib.h>
}
#include <string>

namespace raylib {
    namespace core {
        class Sound {
            public:
                Sound(std::string filepath);
                ~Sound();
                ::Sound loadSound(const std::string fileName);
                bool isSoundPlaying(Music music);
                void unloadSound();
                void playSound();
                void stopSound();
                void pauseSound();
                void resumeSound();
                void setSoundVolume(float volume);
            private:
                ::Sound _music;
        };
    }
}

#endif /*RAYLIB_CORE_MUSIC_HPP_*/