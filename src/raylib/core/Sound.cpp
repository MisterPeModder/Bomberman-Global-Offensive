/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Music
*/

#include "Sound.hpp"

namespace raylib {
    namespace core {
        Sound::Sound(std::string filepath)
        {
            _music = LoadSound(filepath.c_str());
        }
        Sound::~Sound()
        {
        }
        //bool Sound::isSoundPlaying(Sound sound) {return IsSoundPlaying(_music);}
                
        ::Sound Sound::loadSound(const std::string fileName) { return LoadSound(fileName.c_str());}

        void Sound::unloadSound() {UnloadSound(_music);}

        void Sound::playSound() {PlaySound(_music);}

        void Sound::stopSound() {StopSound(_music);}

        void Sound::pauseSound() {PauseSound(_music);}

        void Sound::resumeSound() {ResumeSound(_music);}

        void Sound::setSoundVolume(float volume) {SetSoundVolume(_music, volume);}
    }
}