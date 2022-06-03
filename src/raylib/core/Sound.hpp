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
#include <filesystem>

///raylib namespace
namespace raylib 
{
    namespace core 
    { /// Core namespace (inside of raylib)
        class Sound {
            public:
                /// Consutructor of Sound wich create the sounds
                ///
                /// @param filename Sound path
                Sound(const std::filesystem::path &fileName);
                ~Sound();

                /// Check if sound is playing now
                ///
                /// @retval true if the sound is currently playing
                /// @retval false if the sound is not currently playing
                bool isSoundPlaying();

                /// Unload Sound
                void unloadSound();

                /// plays the sound that has been changed
                void playSound();

                /// Stop the sound currently played
                void stopSound();

                /// Pause the sound currently played
                void pauseSound();

                ///Resumes where the sound was paused
                void resumeSound();

                /// Set the volume of the sound
                void setSoundVolume(float volume);
            private:
                ::Sound _music;
        };
    }
}

#endif /*RAYLIB_CORE_MUSIC_HPP_*/