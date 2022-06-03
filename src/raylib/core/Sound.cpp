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
        Sound::Sound(const std::filesystem::path &fileName) { _music = LoadSound(fileName.generic_string().c_str()); }
        Sound::~Sound() { UnloadSound(_music); }

        bool Sound::isPlaying() { return IsSoundPlaying(_music); }

        void Sound::play() { PlaySound(_music); }

        void Sound::stop() { StopSound(_music); }

        void Sound::pause() { PauseSound(_music); }

        void Sound::resume() { ResumeSound(_music); }

        void Sound::setVolume(float volume) { SetSoundVolume(_music, volume), _volume = volume; }

        float Sound::getvolume() { return _volume; }
    } // namespace core
} // namespace raylib
