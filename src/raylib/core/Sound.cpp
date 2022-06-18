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

        Sound::~Sound()
        {
            if (_sound.stream.buffer)
                UnloadSound(_sound);
        }

        bool Sound::isPlaying()
        {
            if (!_sound.stream.buffer)
                return false;
            return IsSoundPlaying(_sound);
        }

        void Sound::play()
        {
            if (_sound.stream.buffer)
                PlaySoundMulti(_sound);
        }

        void Sound::stop()
        {
            if (_sound.stream.buffer)
                StopSound(_sound);
        }

        void Sound::stopAllMulti() { StopSoundMulti(); }

        void Sound::pause()
        {
            if (_sound.stream.buffer)
                PauseSound(_sound);
        }

        void Sound::resume()
        {
            if (_sound.stream.buffer)
                ResumeSound(_sound);
        }

        void Sound::setVolume(float volume)
        {
            if (_sound.stream.buffer)
                SetSoundVolume(_sound, volume), _volume = volume;
        }

        float Sound::getvolume() { return _volume; }
    } // namespace core
} // namespace raylib
