/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Animation
*/

#ifndef RAYLIB_MODEL_ANIMATION_HPP_
#define RAYLIB_MODEL_ANIMATION_HPP_

extern "C"
{
#include <raylib.h>
}

#include <string>
#include "Model.hpp"

namespace raylib
{
    namespace model
    {
        /// The Animation class
        class Animation {
          public:
            /// Animation constructor. Used to initialize an animation from a file
            /// File format accepted: obj and probably some other
            ///
            /// @param animPath the relative path to the animation to import
            Animation(const std::string &animPath);

            /// Animation destructor
            ~Animation();

            /// Copy constructor
            Animation(const Animation &other);

            /// Copy operator
            Animation &operator=(const Animation &other);

            /// Update a model with this animation
            ///
            /// @param model The model to update
            void updateModel(Model &model);

          private:
            std::string _animationPath;
            ::ModelAnimation *_animations;
            unsigned int _animsCount;
            int _animFrameCounter;
        };
    }
}

#endif /* !RAYLIB_MODEL_ANIMATION_HPP_ */
