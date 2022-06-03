/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Audio
*/

#ifndef RAYLIB_CORE_AUDIO_HPP_
#define RAYLIB_CORE_AUDIO_HPP_

extern "C"
{
#include <raylib.h>
}

/// RayLib namespace
namespace raylib
{
    /// Core namespace inside of raylib
    namespace core
    {
        /// The Audio static class that will initialize audio and manage it
        class Audio {
          public:
            /// Instant audio device
            static void initDevice();

            /// Close audio device
            static void closeDevice();

            /// Return if audio device is ready or not
            ///
            /// @retval true in case if audio device is ready
            /// @retval false in case if audio device is not ready
            static bool isDeviceReady();

            /// Set the global volume of the program
            ///
            ///@param volume set master volume between 0 and 100
            static void setMasterVolume(float volume);
        };
    } // namespace core
} // namespace raylib

#endif /*RAYLIB_CORE_AUDIO_HPP_*/
