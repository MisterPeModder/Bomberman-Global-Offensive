/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Music
*/

#include "Sound.hpp"

///raylib namespace
namespace raylib 
{
    namespace core 
    {
        Sound::Sound(const std::filesystem::path &fileName)
        {
            _music = LoadSound(fileName.generic_string().c_str());
        }
        Sound::~Sound()
        {
            this->unloadSound();
        }

        bool Sound::isSoundPlaying() {return IsSoundPlaying(_music);}

        void Sound::unloadSound() {UnloadSound(_music);}

        void Sound::playSound() {PlaySound(_music);}

        void Sound::stopSound() {StopSound(_music);}

        void Sound::pauseSound() {PauseSound(_music);}

        void Sound::resumeSound() {ResumeSound(_music);}

        void Sound::setSoundVolume(float volume) {SetSoundVolume(_music, volume);}
    }
}