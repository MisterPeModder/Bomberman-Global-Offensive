/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Music
*/

#include "Music.hpp"

/// raylib namespace
namespace raylib
{
    namespace core
    {
        Music::Music(const std::filesystem::path &fileName) { _music = LoadMusicStream(fileName.generic_string().c_str()); }

        Music::~Music()
        {
            if (_music.stream.buffer)
                UnloadMusicStream(_music);
        }

        bool Music::isPlaying()
        {
            if (!_music.stream.buffer)
                return false;
            return IsMusicStreamPlaying(_music);
        }

        void Music::play()
        {
            if (_music.stream.buffer)
                PlayMusicStream(_music);
        }

        void Music::stop()
        {
            if (_music.stream.buffer)
                StopMusicStream(_music);
        }

        void Music::pause()
        {
            if (_music.stream.buffer)
                PauseMusicStream(_music);
        }

        void Music::resume()
        {
            if (_music.stream.buffer)
                ResumeMusicStream(_music);
        }

        void Music::setVolume(float volume)
        {
            if (_music.stream.buffer)
                SetMusicVolume(_music, volume), _volume = volume;
        }

        float Music::getvolume() { return _volume; }
    } // namespace core
} // namespace raylib
