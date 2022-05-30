/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Audio
*/

#ifndef RAYLIB_CORE_AUDIO_HPP_
#define RAYLIB_CORE_AUDIO_HPP_

#include <raylib.h>

namespace raylib
{
    namespace core {
        class Audio {
            public:
                Audio();
                ~Audio();

            protected:
            private:
                ::Sound _sound;
        };
    }
}

#endif /*RAYLIB_CORE_AUDIO_HPP_*/