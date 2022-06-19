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
        class Music {
          public:
            /// Consutructor of Music wich create the musics
            ///
            /// @param filename Music path
            Music(const std::filesystem::path &fileName);
            ~Music();

            /// Check if music is playing now
            ///
            /// @retval true if the music is currently playing
            /// @retval false if the music is not currently playing
            bool isPlaying();

            /// plays the music that has been changed
            void play();

            /// Stop the music currently played
            void stop();

            /// Stop all currently playing musics (using multichannel buffer pool)
            static void stopAllMulti();

            /// Pause the music currently played
            void pause();

            /// Resumes where the music was paused
            void resume();

            /// Set the volume of the music
            void setVolume(float volume);

            /// Get volume of the music
            float getvolume();

          private:
            float _volume;
            ::Music _music;
        };
    } // namespace core
} // namespace raylib

#endif /*RAYLIB_CORE_MUSIC_HPP_*/
