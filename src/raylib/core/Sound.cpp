/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Music
*/

#include "Sound.hpp"

/// raylib namespace
namespace raylib
{
    namespace core
    {
        Sound::Sound(const std::filesystem::path &fileName) { _sound = LoadSound(fileName.generic_string().c_str()); }
        Sound::~Sound() { UnloadSound(_sound); }

        bool Sound::isPlaying() { return IsSoundPlaying(_sound); }

        void Sound::play() { PlaySound(_sound); }

        void Sound::stop() { StopSound(_sound); }

        void Sound::pause() { PauseSound(_sound); }

        void Sound::resume() { ResumeSound(_sound); }

        void Sound::setVolume(float volume) { SetSoundVolume(_sound, volume), _volume = volume; }

        float Sound::getvolume() { return _volume; }
    } // namespace core
} // namespace raylib
