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

#include <filesystem>
#include <string>

/// raylib namespace
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
            bool isPlaying();

            /// plays the sound that has been changed
            void play();

            /// Stop the sound currently played
            void stop();

            /// Pause the sound currently played
            void pause();

            /// Resumes where the sound was paused
            void resume();

            /// Set the volume of the sound
            void setVolume(float volume);

            /// Get volume of the sound
            float getvolume();

          private:
            float _volume;
            ::Sound _music;
        };
    } // namespace core
} // namespace raylib

#endif /*RAYLIB_CORE_MUSIC_HPP_*/
